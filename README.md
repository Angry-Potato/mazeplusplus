# Mazeplusplus
A simple 1 or 2 player maze game, by Liam Humphreys.

## Installation
Clone the github repository using `git clone git@github.com:Angry-Potato/mazeplusplus.git`, or download the source in a zip from [here](https://github.com/Angry-Potato/mazeplusplus/archive/master.zip).

From the root directory, run `make` to list available targets to compile the executable.

Commands available are:
```
make debug		# Compiles mazeplusplus to ./bin/mazepp, runs unit tests, then runs a clean
make release		# Compiles mazeplusplus to ./bin/mazepp with compiler flags to optimise for executable size + speed, runs unit tests, then runs a clean
make mazepp		# Compiles mazeplusplus to ./bin/mazepp, then runs unit tests
make clean		# Removes all *.o files in the project
make unit_test		# Compiles the test executable to ./bin/test_mazepp, then runs unit tests
make dockermazepp	# Runs compilation and unit tests in a container, then copies executables out to ./bin/
make dockerclean	# Removes the mazepp container
make dockercp		# Copies executables out from the mazepp container, and into ./bin
make dockerrun		# Runs given target in mazepp container (defaults to debug)
make dockerbuild	# Builds the mazepp container
```

## Gameplay
Race to get to the heart!

Player 1 controls the cyan face using the arrow keys.

Player 2 controls the red face using WASD.

F1 pauses the game.

ESCAPE quits the game.
