-Battle and Chaos Version 1.0 24-APR-2015-

------------------------------------------------------------------------
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMNmhso//:-----::/oshdNMhmMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMNds/-...................-: `hMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMho-........................  .-+hMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMNy:..........................  .....:sNMMMMMMMMMMMMMMMM
MMMNhmNMMMMMMMMMy-...........................  ........-yNMMMMMMMNmdNMMM
MMMdyhydmMMMMMm/.......................-....  .........../dMMMNmhyyhmMMM
MMMmyyyyyhdmMh-.......................-::--.`.............-hmhyyyyyyNMMM
MMMMmmdhyyyyyo/-./-...................---:hs-:--.....:/.-/syhyhhhdmNMMMM
MMMMhdmmmmhyhhyy-+o+/-................../dm/.-/-..:/+oo:yyyyyymNmmddMMMM
MMMMyhhhydmo/+oy//++o++/-........-://::+dN+...--/+oo+///so+++sdhhhyhMMMM
MMMMmhhhyssyysoo:+++++++++:..-::////+/smmy:-.:++++//+o//oosyyyhyyhhmMMMM
MMMMMNmNNmosssyys:+++o+++/:.-////////smNh///./++++++++:syyssso+dmmNMMMMM
MMMMMmyhddoooo+++://+/////:..////+//smNh///:.://///++/:++++ossshhyNMMMMM
MMMMMNyyhhyyhhhyys/+++++++:..:///+/smmd+///-.:+++oo++:shyyyyyyyyydMMMMMM
MMMMMMMmmd++++oooo+:+++oo+/-..:+/+sNmd+///:.:+++++o+:/+o++++ooodmMMMMMMM
MMMMMMMNhyyyyyyhhyy+:/++++o+:..:/ymNmo///:.:++++/+/:oyyyyyyyyyshMMMMMMMM
MMMMMMMMNhyyysssooooo+++++/-...-ymNmo///-...-/+++/+sooo+ossyhhhNMMMMMMMM
MMMMMMMMMMm+++ooyhhyss/--......yNNms//:........--:syyyyyoooo+/mMMMMMMMMM
MMMMMMMMMMMdsyhhyss/-........-ymmNo................:+osyhyys:yMMMMMMMMMM
MMMMMMMMMMMMs/++:-..........-ymNmy....................-/++:.oMMMMMMMMMMM
MMMMMMMMMMMMMs-............-hNmmy..........................sMMMMMMMMMMMM
MMMMMMMMMMMMMMd:..........-dNNmd-........................-hMMMMMMMMMMMMM
MMMMMMMMMMMMMMMNs-.......-hmmmh-.......................-oNMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMms-.....hmmmm:......................-omMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMNy/-..mNdy:....................-/yNMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMNhsmh/..................-:+ymMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMmhyo/:---------:/oyhmMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNNNmNNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
------------------------------------------------------------------------


INTRODUCTION
------------
'Battle and Chaos' is a real-time multiplayer strategy game. The game is inspired from the tower defence games, which are usually single player. So, we decided to make a all-new version.

This project was made as an assignment in 'Design and Practices in Computer Science' course under Prof. Huzur Saran and guidance of a TA, Prathmesh Kallurkar, a PhD Scholar.


REQUIREMENT
-----------

Operating System    : Linux
Language            : C++
Compiler            : g++
Libraries           : SFML 2.0 Libraries (http://www.sfml-dev.org/)

- Minimum Resolution : 1366 x 768

USAGE
-----

-Running the game

Execute             : make
Debug               : make debug
Print               : make print

- Starting the game

One player has to host the game and others will join. Host will write the number of players in the game. Other players will give team number (1 or 2) and click join button and then give 'IP<space>Port e.g '192.168.0.101 4000'

- Controls (Key Bindings)

W,A,S,D           - Movement of hero
Space bar         - Hero shoots
Left Mouse Click  - Interaction


CONFIGURATION
-------------

I. Texture Images

These are the file names that can be used to change the look of the game.

Menu Background : 'background.png'
...

II. Paths

Paths in the game can be modified in data/path/ directory.

- path1.txt and path2.txt are for team1 and team2 respectively.
- Coordinates of corner points need to be given in these files.
- Valid coordinates belongs to A = {0,1...,33} * {1,2...,15}
- Difference between two consecutive coordinates should be (0,y) or (x,0) for desirable effect otherwise crash or something else.

III. Sounds

Sounds used in the game.

FILES INCLUDED
--------------
Source Code:
-See documentations for complete details.

Data files:
    images/
    path/path1.txt path/path2.txt
    sounds/ 7 files

Other Files:

    This Readme.txt
    Reference Documentations
    Design Document
    makefile


TROUBLESHOOTING
---------------

Refer to FAQ.
Any bug? Report us.


FAQ
---

Q. Error like library XYZ not found during compilation?
A. Make sure all the libraries listed are installed on the system. Search for the suitable package for XYZ library.

Q. Some file not found error is coming?
A. Texture files might not present in the ./files directory. Refer to CONFIGURATION section.

Q. Any Fullscreen issues??
A. You can turn off the full screen mode in 'game.cpp' file.

Q. How do I see my IP/Port while hosting?
A. Default port is set as 4000. Use ifconfig -a command in linux to see your local ip. Or see the output of the terminal.


MAINTAINERS
-----------
Patidar, Harishchandra - patidarharish83@gmail.com
Rohit                  - ricjhander135@gmail.com
Kumar, Sachin          - sachinkmr571@gmail.com
Kataria, Manoj         - manoj.mkataria@gmail.com


BUG REPORTING/SUGGESTIONS
-------------------------
User may report any bug, issues, improvement suggestions/feedback to us. Send maintainers an email with subject "BATTLE AND CHAOS - FEEDBACK"


Resources
---------
Sound files are taken from SoundBible. http://soundbible.com/
Textures (Logo, images, backgrounds) are created by Sachin Kumar (sachinkmr571@gmail.com) in Adobe Photoshop, GIMP Image Editor.

-