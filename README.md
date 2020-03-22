# TeamSpeak 3 Queue Vulture Plugin
Designed by Michael T. Meikle
Started on 03/22/2020

## Getting Started 

Install queue_vulture_(platform).dll into your %appdata%/TS3Client/plugins folder

Note: This plugin is not compatible with MacOS at this time.

## Commands

Keyword: vulture

lock
 - Sets whatever channel you currently have selected in the TS GUI as monitored
 - Defaults to an expected channel client limit of 4
 - Optional 2nd arguement specifies a user defined channel client limit (Takes an int)
unlock
 - Clears the set channel lock
clear
 - Same functionality as unlock
status
 - Gives a readout of currently monitored channel if one exists 