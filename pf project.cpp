#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>
#include <stdexcept>

using namespace std;

const int MATRIX_SIZE = 5; // Defines the 5x5 grid
const int MATRIX_ELEMENTS = MATRIX_SIZE * MATRIX_SIZE; // Total positions (25)

// Function to initialize the hidden points in the grid
void initializeMatrix(int* matrix, int& hiddenIndex1, int& hiddenIndex2, int& hiddenIndex3, int& hiddenIndex4) {
    hiddenIndex1 = rand() % MATRIX_ELEMENTS;
    hiddenIndex2 = rand() % MATRIX_ELEMENTS;
    hiddenIndex3 = rand() % MATRIX_ELEMENTS;
    hiddenIndex4 = rand() % MATRIX_ELEMENTS;

    while (hiddenIndex2 == hiddenIndex1) hiddenIndex2 = rand() % MATRIX_ELEMENTS;
    while (hiddenIndex3 == hiddenIndex1 || hiddenIndex3 == hiddenIndex2) hiddenIndex3 = rand() % MATRIX_ELEMENTS;
    while (hiddenIndex4 == hiddenIndex1 || hiddenIndex4 == hiddenIndex2 || hiddenIndex4 == hiddenIndex3) hiddenIndex4 = rand() % MATRIX_ELEMENTS;

    for (int i = 0; i < MATRIX_ELEMENTS; i++) {
        matrix[i] = (i == hiddenIndex1 || i == hiddenIndex2 || i == hiddenIndex3 || i == hiddenIndex4) ? 1 : 0;
    }
}

// Function to display a 5x5 grid with positions numbered
void displayMatrix() {
    cout << "Grid positions (1-25):" << endl;
    int position = 1;
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            cout << setw(3) << position++ << " ";
        }
        cout << endl;
    }
}

// Function to handle a player's turn
bool playTurn(const string& playerName, int* matrix) {
    int guess;
    while (true) {
        try {
            cout << "\n" << playerName << ", enter your guess (1-25): ";
            cin >> guess;

            if (cin.fail()) {
                throw invalid_argument("Invalid input! Please enter a number.");
            }
            if (guess < 1 || guess > MATRIX_ELEMENTS) {
                throw out_of_range("Out of range! Enter a number between 1 and 25.");
            }
            break; // Input is valid, exit the loop
        } catch (const invalid_argument& e) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Error: " << e.what() << endl;
        } catch (const out_of_range& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    if (matrix[guess - 1] == 1) {
        cout << "Congratulations, " << playerName << "! You found a hidden point!" << endl;
        matrix[guess - 1] = 0; // Mark the point as found
        return true;
    } else {
        cout << "No hidden point here. Better luck next time!" << endl;
        return false;
    }
}

// Function to log the winner's name to a file
void logWinner(const string& winnerName) {
    try {
        ofstream file("game_winners.log", ios::app);
        if (!file) {
            throw runtime_error("Error: Unable to open the log file.");
        }
        file << "Winner: " << winnerName << endl;
        file.close();
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }
}

// Function to play the game
void playGame() {
    srand(static_cast<unsigned int>(time(0)));

    int numPlayers;
    while (true) {
        try {
            cout << "Enter the number of players (2-4): ";
            cin >> numPlayers;

            if (cin.fail()) {
                throw invalid_argument("Invalid input! Please enter a number.");
            }
            if (numPlayers < 2 || numPlayers > 4) {
                throw out_of_range("Out of range! Enter a number between 2 and 4.");
            }
            break;
        } catch (const invalid_argument& e) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: " << e.what() << endl;
        } catch (const out_of_range& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    string players[4];
    for (int i = 0; i < numPlayers; i++) {
        cout << "Enter Player " << (i + 1) << "'s name: ";
        cin >> players[i];
    }

    int scores[4] = {0};
    int matrix[MATRIX_ELEMENTS];
    int hiddenIndex1, hiddenIndex2, hiddenIndex3, hiddenIndex4;

    initializeMatrix(matrix, hiddenIndex1, hiddenIndex2, hiddenIndex3, hiddenIndex4);
    displayMatrix();

    bool continueGame = true;
    while (continueGame) {
        for (int round = 1; round <= 3; round++) {
            cout << "\n--- Round " << round << " ---" << endl;
            for (int i = 0; i < numPlayers; i++) {
                cout << "\n" << players[i] << "'s turn:" << endl;
                if (playTurn(players[i], matrix)) {
                    scores[i]++;
                }
                cout << players[i] << "'s current score: " << scores[i] << endl;
            }
        }

        string choice;
        while (true) {
            try {
                cout << "\nDo you want to play another round? (yes/no): ";
                cin >> choice;
                if (choice != "yes" && choice != "no" && choice != "Yes" && choice != "No" && choice != "y" && choice != "n" && choice != "Y" && choice != "N") {
                    throw invalid_argument("Invalid input! Please enter 'yes' or 'no'.");
                }
                break;
            } catch (const invalid_argument& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
        continueGame = (choice == "yes" || choice == "y" || choice == "Y" || choice == "Yes");
    }

    int maxScore = 0;
    string winner;
    bool tie = false;

    for (int i = 0; i < numPlayers; i++) {
        if (scores[i] > maxScore) {
            maxScore = scores[i];
            winner = players[i];
            tie = false;
        } else if (scores[i] == maxScore) {
            tie = true;
        }
    }

    if (tie) {
        cout << "\nIt's a tie! Well played, everyone!" << endl;
    } else {
        cout << "\nCongratulations, " << winner << "! You are the winner!" << endl;
        logWinner(winner);
    }
}

int main() {
    char playAgain;
    do {
        playGame();
        while (true) {
            try {
                cout << "\nDo you want to play the game again? (y/n): ";
                cin >> playAgain;
                if (playAgain != 'y' && playAgain != 'Y' && playAgain != 'yes' && playAgain != 'Yes' && playAgain != 'n' && playAgain != 'N' && playAgain != 'no' && playAgain != 'No') {
                    throw invalid_argument("Invalid input! Please enter 'y' or 'n'.");
                }
                break;
            } catch (const invalid_argument& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    } while (playAgain == 'y' || playAgain == 'Y' || playAgain == 'Yes' || playAgain == 'yes');

    cout << "Thank you for playing! Goodbye!" << endl;
    return 0;
}
