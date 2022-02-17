I made a Barbie Dream house text adventure. The player must guess who murdered Barbie's dog Taffy. I divided the
project into c files which are rooms, items, and then adventure. The gameboard was constructed through pointers
which were linked up to other room pointers depending on their position on the board. The pointers were also randomly
assigned a room. The items file initializes the items to each room and the adventure file is where the majority
of the implementation is. Adventure executes the game while keeping track of the game state and updating objects
accordingly. The user is represented by an avatar struct which keeps track of its current location and inventory.
The user can change the state of avatar by typing commands which call corresponding methods. The state of the game is
always checked before a user types in a command.

The game manages input by prompting the user for commands. The user must type a single word command with no
spaces or shifts and press enter to receive feedback from the program. If the user types an invalid command, they
will have to retype the command. If the user types an an invalid input, the game will prompt the user to retry the
input for the same command. Input can have spaces, however commands must be one word. Character guesses must start
with upper case letters and commands, directions, and items must start with lowercase letters.

Type the command: "./game" to begin

good luck! Barbie is counting on you...
