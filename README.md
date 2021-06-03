## summary

This game is implemented in C++ object-oriented programming.  Contains classes and objects and other object-oriented programming implementations.  A prototype of the Battleship game.
Battleship is a war-themed board game for two players in which the opponents try to guess the location of their opponent's warships and sink them. In this variation, you have the option to play against a computer, play against a person, or have the computer play by itself and also this variation has the option to increase the size of the board. Each player hides their ship on a a console generated grid containing vertical and horizontal coordinates like Excel. Players take turns calling out row and column coordinates on the other player's grid to identify a square that contains a ship. Neither you nor the other player can see the other's board. The game is won when one player has sunk all the other players ships. In order to achieve this, I’ll allow the player to setup his own board by placing multiple ships of different sizes as outlined in the requirements. Since the size of the board and the length of the ships may vary and should have the option to be changed, all the information needed to play the game would be placed in a config file and read using file reader algorithm. I’ll would need to prompt a player to take their turn at hitting a ship by inputting a coordinate. 

The game’s modes of play is been selected at the main interface of the game.
-	Single player
-	Multi Player 


The type of ship/boat can also be selected at the first interface of the game.
The types include:
- Carrier
- Battleship 
-	Destroyer 
- Submarine 
- Patrol


Exceptions are handled successfully in the game to prevent the user from entering outrageous figures/numbers in the game. 
The next interface is the game where the game is played.

## game mode
PC vs Player – if this option selected, the player will have to place their ships on the board / battleground. A coordinate that describes a specific point on a 2D board is given which is then used to place the boat at the given coordinate. This process is done multiple times until all boats are successfully played on the board. Random generated coordinates are used to place the computer’s boats on the board. If a player hits a ship, it will still be the turn to hit a ship until they miss. If the right hit is made on the board by spotting the correct location of the enemy shit. You made a hit...!! Congrats!!!!!!  Whoever sinks each other ships or boats first wins.

Player vs Player – Same concept as above except none of the boats are auto placed and the is two different people playing against each other.


## user stories
-	As a player I want the computer to set up its own board so that I don't know where the opponent’s ships are placed. 
-	As a player I want to see where my ships are being hit on my board.
-	As a player I want to see where I previously hit my opponent’s board so I can make my next hit
-	As a player I want to set up my board
-	As a player I want to select the square I'm attacking
-	As a player I want to know who has won.

## object-oriented design ideas and plan
- Not repeating lines of wherever possible. ie. using a DRY approach
- Breaking down requirements into classes and objects
- Self-explanaory names for readability
- commenting code for re-usability and readablitity
- Seperating classes into different files

## code review
Project was built using a battleship boilerplate - https://github.com/mike-ada/AdaShip-version-1

Instead of using a 2d array for the board, a an index is used to identify a specific coordinate on the board. The board is created using the configuration file - ada_config.ini
The width of the board is used alongside the index to determine the rol and column. The division of idx and witdth is the row and the remainder is the column

<img alt="code5" src="https://raw.githubusercontent.com/mannyuk-dev/battleship---oop/main/2021-06-03%2012_06_33-coordinates.cpp%20-%20AdaShip-version-1-main%20-%20Visual%20Studio%20Code.png">

To identify wheter a coordinate has already been hit, a simple function is used. if a coordinate is not hit, is marked as Available. This helps us differentiate what has been hit and what hasn't been hit

<img alt="code5" src="https://raw.githubusercontent.com/mannyuk-dev/battleship---oop/main/image.png">

The game flow is very easy to understand. When a user selects a game mode, the value is stored and used in a switch statement to select the game type, the game is then initialised using the intitgame function/method which takes two arguments - config file and the game mode selected. This is used to set up the game as requested by the user.
on line 467 the player's boat is rendered in the console and then they are asked where they'd like to place their boats on line 469

![image](https://user-images.githubusercontent.com/56549229/120637548-f5887080-c466-11eb-824e-afa742d2d8e5.png)





