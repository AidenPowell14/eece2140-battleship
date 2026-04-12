# Battleship

## Overview

This is the final project for Northeastern University’s EECE2140, developed by Elliot Hill and Aiden Powell. This project implements a terminal-based version of the traditional board game Battleship using object oriented C++, and features a design sufficiently modular to be replaced in the future by a GUI-based system, AI players, and more.

## Quick Start
Compile: `make build`
Run standard game: `make std`
Run small demo game: `make small`
Clean: `make clean`

Program arguments: `./battleship-game \<num rows> \<num cols> \<filepath the red ships> \<filepath to blue ships>`
Ship files should include only whitespace-separated integers. See `docs/standard.ships` as an example.

## Main Functionalities 
- Start game - Allows user to choose grid size, number of ships, types of ships
- Ship Placement - Allows user to place ships on the game board
- Strike - lets the user attack a grid point

### Starting the game 

1. Program starts from the command line with arguments regarding the board size and the ships to play with for each player. (input two numbers and compile the program using the desired ship config file) 
2. After initializing, the program will display a screen discussing input syntax and basic rules. Each player
can start with a different set of linear ships. 
3. Ship files must contain a series of whitespace-separated integers represeting the sizes of each of their ships.
- Input: number of rows, number of columns, filepath to ships for each player
- Output: Begins first prompt for ship placement from each player
- Contribution: Launches the program

### Ship Placement

1. In order, players are prompted to add their ships to their own boards. After this phase, it is impossible to edit one’s ship configuration. As explained
in the rules, ships grow either downward or rightward (depending on orientation).
2. Position requests that are out of bounds or would intersect with preexisting ships
are rejected. Once one player has placed all of their ships, a mutual confirmation
screen prompts player transition acknowledgment, and then the process is repeated
for the other player.
- Input: Row, column, and orientation
- Output: Confirmation of successful ship placement and proceeding to the next
- Contribution: Sets the game state for the rest of the game.

### Strike

1. Players take turns firing missiles at locations on each other’s boards
until one player is left without any ships left. 
2. Each guess immediately returns a hit/miss report to the attacker, and then prompts another mutual confirmation
screen. If a complete battleship would be sunk as the result of an attack, an
additional notification is raised, and the end of game condition is checked.
3. An opponent’s strikes against a player are not displayed on the victim’s HitBoard unless the strike resulted in a direct hit.
- Input: Row and column
- Output: Hit/miss report, sunken battleship notification, end of game notification
- Contribution: Primary gameplay loop revolves around this process



#### Project structure: 

``` 
battleship/
|--- src/
|   |--- include/
|   |   |--- Controller.h
|   |   |--- data.h
|   |   |--- HitBoard.h
|   |   |--- Model.h
|   |   |--- ShipBoard.h
|   |   |--- ShiPReader.h
|   |--- battleship.cpp      % main program
|   |--- Controller.cpp
|   |--- HitBoard.cpp
|   |--- Model.cpp
|   |--- ShipBoard.cpp
|   |--- ShipReader.cpp
|--- docs/
|   |--- invalid.ships
|   |--- standard.ships
|   |--- tiny.ships
|   |--- TechnicalReport.pdf
|--- src-old/                        
|   |--- ...     % 20+ classes preserved for posterity
|--- Makefile
`--- README.md
```
