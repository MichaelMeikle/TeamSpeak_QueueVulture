# TeamSpeak 3 Queue Vulture Plugin
 - Designed by Michael T. Meikle
 - Started on 03/22/2020
 
 ## Purpose
 Originally developed for use in the Department of Justice Roleplay (DOJRP) FiveM community. Designed to make grabbing TeamSpeak queue spots incredibly easy without having to monitor the channel and allows the user to nearly always beat everyone else to get the spot thanks to the speed of the script. Decided to release this for public consumption/alteration.
 
## Getting Started 

Install queue_vulture_(platform).dll into your %appdata%/TS3Client/plugins folder

Note: This plugin is not compatible with MacOS at this time.

## Commands

Keyword: vulture

lock
 - Sets whatever channel you currently have selected in the TS GUI as monitored
 - Defaults to MAXCLIENTS channel variable
 - Optional 2nd arguement specifies a user defined channel client limit (Takes an int)
 
unlock
 - Clears the set channel lock
 
clear
 - Same functionality as unlock
 
status
 - Gives a readout of currently monitored channel if one exists 
