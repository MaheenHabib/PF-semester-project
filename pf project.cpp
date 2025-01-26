#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

const int MATRIX_SIZE = 5; // Defines the square matrix size (5x5)
const int MATRIX_ELEMENTS = MATRIX_SIZE * MATRIX_SIZE; // Total elements in the matrix

void initializeMatrix(int* matrix, int& hiddenIndex1, int& hiddenIndex2, int& hiddenIndex3, int& hiddenIndex4) {
    hiddenIndex1 = rand() % MATRIX_ELEMENTS; // Random position between 0 and MATRIX_ELEMENTS-1
    hiddenIndex2 = rand() % MATRIX_ELEMENTS;
    hiddenIndex3 = rand() % MATRIX_ELEMENTS;
    hiddenIndex4 = rand() % MATRIX_ELEMENTS;

    // Ensure all hidden indices are unique
    while (hiddenIndex2 == hiddenIndex1) hiddenIndex2 = rand() % MATRIX_ELEMENTS;
    while (hiddenIndex3 == hiddenIndex1 || hiddenIndex3 == hiddenIndex2) hiddenIndex3 = rand() % MATRIX_ELEMENTS;
    while (hiddenIndex4 == hiddenIndex1 || hiddenIndex4 == hiddenIndex2 || hiddenIndex4 == hiddenIndex3) hiddenIndex4 = rand() % MATRIX_ELEMENTS;

    for (int i = 0; i < MATRIX_ELEMENTS; i++) {
        matrix[i] = (i == hiddenIndex1 || i == hiddenIndex2 || i == hiddenIndex3 || i == hiddenIndex4) ? 1 : 0;
    }
}

void displayMatrix() {
    cout << "Matrix positions:" << endl;
    int position = 1;
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            cout << setw(3) << position++ << " "; // Proper spacing for alignment
        }
        cout << endl;
    }
}

bool playTurn(const string& playerName, int* matrix, int hiddenIndex1, int hiddenIndex2, int hiddenIndex3, int hiddenIndex4) {
    int guess;
    while (true) {
        cout << "\n" << playerName << ", enter your guess (1-" << MATRIX_ELEMENTS << "): ";
        cin >> guess;

        if (cin.fail() || guess < 1 || guess > MATRIX_ELEMENTS) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between 1 and " << MATRIX_ELEMENTS << "." << endl;
        } else {
            break;
        }
    }

    if (matrix[guess - 1] == 1) {
        cout << "Congratulations, " << playerName << "! You found a hidden point!" << endl;
        return true;
    } else {
        cout << "Wrong guess." << endl;
        return false;
    }
}

void logWinner(const string& winnerName) {
    ofstream file("game_winners.log", ios::app);
    if (file.is_open()) {
        file << "Winner: " << winnerName << endl;
        file.close();
    } else {
        cerr << "Unable to write to the log file." << endl;
    }
}

void playGame() {
    srand(static_cast<unsigned int>(time(0)));

    // Get number of players
    int numPlayers;
    do {
        cout << "Enter the number of players (2-4): ";
        cin >> numPlayers;
        if (numPlayers < 2 || numPlayers > 4) {
            cout << "Invalid input! Please enter a number between 2 and 4." << endl;
        }
    } while (numPlayers < 2 || numPlayers > 4);

    string players[4];
    for (int i = 0; i < numPlayers; i++) {
        cout << "Enter Player " << (i + 1) << " name: ";
        cin >> players[i];
    }

    int scores[4] = {0};
    int matrix[MATRIX_ELEMENTS];
    int hiddenIndex1, hiddenIndex2, hiddenIndex3, hiddenIndex4;

    initializeMatrix(matrix, hiddenIndex1, hiddenIndex2, hiddenIndex3, hiddenIndex4);
    displayMatrix();

    bool continueRound = true;
    while (continueRound) {
        for (int attempt = 0; attempt < 3; attempt++) { // 3 attempts per player per round
            for (int i = 0; i < numPlayers; i++) {
                cout << "\n" << players[i] << "'s turn (Attempt " << (attempt + 1) << "):" << endl;
                if (playTurn(players[i], matrix, hiddenIndex1, hiddenIndex2, hiddenIndex3, hiddenIndex4)) {
                    scores[i]++;
                }
                cout << players[i] << "'s current score: " << scores[i] << endl;
            }
        }

        // Ask if players want another round
        string choice;
        do {
            cout << "\nDo you want to play another round? (yes/no): ";
            cin >> choice;
            if (choice == "yes" || choice == "YES" || choice == "Yes" || choice == "y" || choice == "Y") {
                continueRound = true;
            } else if (choice == "no" || choice == "NO" || choice == "No" || choice == "n" || choice == "N") {
                continueRound = false;
                cout << "Thank you for playing! Calculating final scores..." << endl;
            } else {
                cout << "Invalid input. Please enter 'yes' or 'no'." << endl;
            }
        } while (choice != "yes" && choice != "YES" && choice != "Yes" && choice != "y" && choice != "Y" &&
                 choice != "no" && choice != "NO" && choice != "No" && choice != "n" && choice != "N");
    }

    // Determine the winner
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
        cout << "\nIt's a tie! Great effort from all players." << endl;
    } else {
        cout << "\nCongratulations, " << winner << "! You win the game!" << endl;
        logWinner(winner);
    }
}

int main() {
    bool playAgain = true;
    while (playAgain) {
        playGame();

        // Ask to play the entire game again
        string choice;
        do {
            cout << "\nDo you want to restart the game? (yes/no): ";
            cin >> choice;
            if (choice == "yes" || choice == "YES" || choice == "Yes" || choice == "y" || choice == "Y") {
                playAgain = true;
            } else if (choice == "no" || choice == "NO" || choice == "No" || choice == "n" || choice == "N") {
                playAgain = false;
                cout << "Thank you for playing! Goodbye!" << endl;
            } else {
                cout << "Invalid input. Please enter 'yes' or 'no'." << endl;
            }
        } while (choice != "yes" && choice != "YES" && choice != "Yes" && choice != "y" && choice != "Y" &&
                 choice != "no" && choice != "NO" && choice != "No" && choice != "n" && choice != "N");
    }

    return 0;
}
