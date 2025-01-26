# Matrix Quest

The Hidden Points Game is a simple multiplayer console-based game built in C++. Players take turns guessing grid positions to find hidden points within a 5x5 grid. The game supports 2-4 players, keeps track of scores, and logs the winner's name to a file.

This project demonstrates basic programming concepts such as:

- Loops and conditionals

- Arrays

- User-defined functions

- File handling

- Exception handling


## Features

- Multiplayer support: 2 to 4 players.

- Randomized grid: Hidden points are randomly placed each game.

- Score tracking: Tracks player scores across rounds.

- File logging: Logs the winner’s name to a file(game_winners.log).

- Input validation: Ensures valid user input using exception handling.

- Replay functionality: Players can replay the game.
## How to Play

- The program will prompt you to enter the number of players (2-4).

- Each player provides their name.

- The game displays a 5x5 grid with positions numbered from 1 to 25.

- Players take turns guessing a position on the grid.

- If a hidden point is found, the player earns a point.

- If not, the turn passes to the next player.

- After three rounds, the scores are calculated, and the winner is declared.

- Players can choose to play another round or exit.
## Files

- game_winners.log: Stores the names of the winners for each game session.
## How to Run

- Copy the code into a .cpp file (e.g., hidden_points_game.cpp).

- Compile the code using a C++ compiler, e.g.,

g++ hidden_points_game.cpp -o hidden_points_game

- Run the compiled program:

./hidden_points_game


## Known Issues

- Limited to 4 players.
- The 5x5 grid size is fixed and cannot be changed.
- No visual feedback other than text.

## Future Improvements

- Add a graphical user interface (GUI).
- Include a timer for each player's turn.
- Support for saving and loading game progress.
- Dynamic grid size (e.g., 5x5, 10x10) based on user selection.

## Authors

This project was developed as part of a beginner-level C++ programming exercise to demonstrate key concepts like file handling, exception handling, and user input validation.

