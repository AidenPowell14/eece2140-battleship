# Battleship

## Overview

This is the final project for Northeastern University’s EECE2140, developed by Elliot Hill and Aiden Powell. This project implements a terminal-based version of the traditional board game Battleship using object oriented C++, and features a design sufficiently modular to be replaced in the future by a GUI-based system, AI players, and more.

## Current Progress
As of 4/1/26: Model and view documentation is complete. Many other files exist without declarations. Progress toward implementation of model is underway.z

## Main Functionalities 
- Launchable with CLI arguments 
- Start game - allows user to choose grid size, number of ships, types of ships
- Ship placement - allows user to place ships on the game board
- Strike location - lets user attack a grid point
- Display  Strike grid - lets user keep track of where they have chosen to attack
- Ship grid - lets user keep track of their ships - no input after placement

## Design Summary
Below are the primary functionalities a user can interface with

### Starting the game 

1. Inputs: number of rows (type number and press enter), number of columns (type number and press enter), filepath to Player 1 ships config, filepath to Player 2 ships config.
2. Prompt to begin ship placement

### Ship Placement
1. While unplaced Ships remain for a player:
    - Inputs: player to place for, Ship to place, Point to place at, orientation of Ship (In Letter , Number, Orientation format ex. A1H)
    - Validate placement (press enter)
2. When player 1 has no more ships remaining: repeat the previous step until no ships remain for player 2.
3. ShipBoard receives ship placement, ShipBoard stores location of Ship vector as part of a player profile as passes it to the Model
4. When max number of ships in list reached, prompt player to confirm, when confirmed, seal ShipBoard from future mutation.


**Strike**
1. Inputs: player to be struck, Point to be struck.
2. GameModel receives player intention to strike, checks against player’s own HitBoard to check for attempting to strike previously struck position. If so, fail; if not, forward Point to opponent’s ShipBoard.
3. ShipBoard checks if the Point contains a ship vector; if not, return MISS. If so, forwards strike to relevant ShipNode and return HIT. 
4. ShipNode increments total hits for its own Ship wrapper object. If the relevant Ship’s hits are equal to its total size, it has been sunk. 
5. If a ShipNode’s ship has been sunk, return to ShipBoard SUNK, else FLOAT.
6. If ShipBoard receives SUNK, publish notification to Controller that a Battleship has been sunk.
7. GameModel receives HIT or MISS from ShipBoard; in either case, update the striking player’s HitBoard.
8. GameModel notifies Controller of new player turn.

**Display Strike Grid**
1. Controller prompts View to display to user the HitBoard
2. View forwards request to composed HitView with a const GameModel reference
3. HitView retrieves HitBoard from GameModel
4. Have HitView print GameModel reference

**Ship Grid**
1. Controller prompts View to display to user the ShipBoard
2. View forwards request to composed ShipView with a const GameModel reference
3. ShipView retrieves ShipBoard from GameModel
4. Have ShipView print GameModel reference
