NAME: 	    Kevin Terceros
STUDENT ID: 5078969
COURSE:     CS3790
PROJECT:    Lab 4

# Conway's Game of Life Ver. 3

## Contents of this file

  - Introduction
  - Project Creation
  - Program Execution
    - Constraints
  - User Input
  - Expected Output
  - Program Termination

## Introduction

This project is the developer's third implementation of Conway's Game of Life. The game is intended to be viewed as a
board of living cells, shown as either an 'X' or a [blank] to indicate that the "cell" is "alive" or "dead".

The game works by implementing four basic rules:
	1. If a live cell is adjacent to 0 or 1 live cells, the cell dies as if from underpopulation.
	2. If a live cell is adjacent to 2 or 3 live cells, the cell lives on to the next "generation".
	3. If a live cell is adjacent to 4 or more live cells, the cell dies as if from overpopulation.
	4. If a dead cell is adjacent to exactly 3 live cells, the cell comes to life.

This version was built directly upon Version 2 with changes made to utilize threads to complete its task.

## Project Creation

The user shall create their project by entering "make" in the command line. This creates an executable under the name
"gol". To remove this file, the user shall enter "make clean" in the command line, which will then request
confirmation. Entering 'y' (upper- or lower- case)at this stage will cause the file to be deleted. Entering any other
key will cancel the deletion process and leave the file intact.

## Program Execution

The user shall execute this program through the command line by entering four arguments in the format
"./gol <side_length> <procs_per_side> <num_gens>" in the command line.

- The value <side_length> will be the number of cells on each side of the board where <side_length> x <side_length> are
  the dimensions of the board.

- The value <procs_per_side> will be the number of threads on each side of the board where the total number of threads
  being executed equals <procs_per_side> x <procs_per_side>.

- The value <num_gens> will be the number of "generations" that will be printed out where each generation is a
  configuration of cells created according to the rules outlined in the "Introduction" section.

### Constraints

- The user must enter exactly four arguments. If the user enters any other number of arguments, they will be met with
  a "Malformed request" error.

- The integer values entered in arguments 2-4 must be positive values. If the user enters an integer less than 1, they
  will be met with a "Malformed request" error.

- The value of <side_length> must be evenly divisible by <procs_per_side>. If this condition is not met, the user will
  be met with a "Malformed request" error.

- While the program accepts any sort of input is as values for arguments 2-4 (provided it is not an integer with a
  value less than 1), it is strongly recommended that the user enters integer values in those places. The developer
  cannot guarantee the outcome if the user enters a non-integer value.

- A few important notes:
  - The developer cannot guarantee that the board will be displayed as expected if the value of <side_length> is
    greater than the dimensions of the terminal itself.
  - The user should be advised that values for <num_gens> above 1000 have not been tested.

## User Input

After entering these arguments, the user will be prompted to left-click on the screen. If the user clicks on a space
that either is blank or has not yet been interacted with, that space will be replaced with an 'X'. If the user clicks
on a space with an 'X', the space will turn blank. The user shall press 'q' when finished changing the board. The
configuration of the 'X's and [blanks] on the board becomes the starting generation of the game, where each 'X' is a
"live" cell and each [blank] is a "dead" cell.

- The user is advised not to click outside of the boundaries of the board as defined by <side_length>, as they may be
  met with a "Segmentation fault" error.

## Expected Output

Upon pressing 'q' the user shall expect to see a series of generations (defined by the <num_gens> argument), each
changing the board configuration according the rules outlined under the "Introduction". The first of these generations
will be based on the user's configuration.

## Program Termination

After running for the number of generations specified by the user, the program will terminate on its own.