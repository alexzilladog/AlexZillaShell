# AlexZillaShell
RESEARCH PURPOSES ONLY. A reverse shell in C with persistence via the Windows registry, evades most AV. Flipper zero script included

I made this project to better understand how reverse shells work, as well as techniques used to deploy them.  
During this project I had 2 main problems:
1. I had some trouble finding a way to actually communicate with the shell, which led me to use a port forwarded VPN (Proton), but there was a problem with the IP and Port constantly changing. This led me to use curl commands on pastebin to actually get the port and ip, with the drawback of having to manually update the port and ip on the repsective bins. 
2. I also had some trouble finding a way to actually deploy the executable via the flipper. A lot of systems may not have gcc or any programming languages installed, so it wouldn't make sense to write out the code in a rubber ducky script, I instead hosted the compiled executable on GoFile, and used a powershell script with Invoke-WebRequest to retrieve it. It didnt work the first few times, but eventually I found that firefox had a "Copy powershell" command for get requests in it's network tab, which worked, but made the script much more complicated. The flipper zero script takes about 13 seconds to complete, but it requires a bluetooth or physical connection.
