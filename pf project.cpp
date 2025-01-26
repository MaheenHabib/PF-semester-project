#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>

using namespace std;

const int MATRIX_SIZE = 5; // Defines the 5x5 grid
const int MATRIX_ELEMENTS = MATRIX_SIZE * MATRIX_SIZE; // Total positions (25)

// Function to initialize the hidden points in the grid
void initializeMatrix(int* matrix, int& hiddenIndex1, int& hiddenIndex2, int& hiddenIndex3, int& hiddenIndex4) {
    // Generate random unique positions for hidden points
    hiddenIndex1 = rand() % MATRIX_ELEMENTS;
    hiddenIndex2 = rand() % MATRIX_ELEMENTS;
    hiddenIndex3 = rand() % MATRIX_ELEMENTS;
    hiddenIndex4 = rand() % MATRIX_ELEMENTS;

    while (hiddenIndex2 == hiddenIndex1) hiddenIndex2 = rand() % MATRIX_ELEMENTS;
    while (hiddenIndex3 == hiddenIndex1 || hiddenIndex3 == hiddenIndex2) hiddenIndex3 = rand() % MATRIX_ELEMENTS;
    while (hiddenIndex4 == hiddenIndex1 || hiddenIndex4 == hiddenIndex2 || hiddenIndex4 == hiddenIndex3) hiddenIndex4 = rand() % MATRIX_ELEMENTS;

    // Fill the matrix: 1 for hidden points, 0 otherwise
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
        cout << "\n" << playerName << ", enter your guess (1-25): ";
        cin >> guess;

        if (cin.fail() || guess < 1 || guess > MATRIX_ELEMENTS) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input! Please enter a number between 1 and 25." << endl;
        } else {
            break;
        }
    }

    // Check the guessed position
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
    ofstream file("game_winners.log", ios::app); // Append mode
    if (file.is_open()) {
        file << "Winner: " << winnerName << endl;
        file.close();
    } else {
        cerr << "Error: Unable to write to the log file." << endl;
    }
}

// Function to play the game
void playGame() {
    srand(static_cast<unsigned int>(time(0))); // Seed random number generator

    // Get the number of players
    int numPlayers;
    do {
        cout << "Enter the number of players (2-4): ";
        cin >> numPlayers;
        if (numPlayers < 2 || numPlayers > 4) {
            cout << "Invalid input! Please enter a number between 2 and 4." << endl;
        }
    } while (numPlayers < 2 || numPlayers > 4);

    // Get player names
    string players[4];
    for (int i = 0; i < numPlayers; i++) {
        cout << "Enter Player " << (i + 1) << "'s name: ";
        cin >> players[i];
    }

    // Initialize scores and hidden points
    int scores[4] = {0};
    int matrix[MATRIX_ELEMENTS];
    int hiddenIndex1, hiddenIndex2, hiddenIndex3, hiddenIndex4;

    initializeMatrix(matrix, hiddenIndex1, hiddenIndex2, hiddenIndex3, hiddenIndex4);
    displayMatrix();

    // Game rounds
    bool continueGame = true;
    while (continueGame) {
        for (int round = 1; round <= 3; round++) { // 3 rounds
            cout << "\n--- Round " << round << " ---" << endl;
            for (int i = 0; i < numPlayers; i++) {
                cout << "\n" << players[i] << "'s turn:" << endl;
                if (playTurn(players[i], matrix)) {
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
            if (choice == "yes" || choice == "y" || choice == "YES" || choice == "Y") {
                continueGame = true;
            } else if (choice == "no" || choice == "n" || choice == "NO" || choice == "N") {
                continueGame = false;
                cout << "Final scores are being calculated..." << endl;
            } else {
                cout << "Invalid input. Please enter 'yes' or 'no'." << endl;
            }
        } while (choice != "yes" && choice != "y" && choice != "no" && choice != "n");
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
        cout << "\nIt's a tie! Well played, everyone!" << endl;
    } else {
        cout << "\nCongratulations, " << winner << "! You are the winner!" << endl;
        logWinner(winner); // Log the winner to a file
    }
}

int main() {
    char playAgain;
    do {
        playGame();
        cout << "\nDo you want to play the game again? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thank you for playing! Goodbye!" << endl;
    return 0;
}
