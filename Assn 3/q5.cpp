#include <bits/stdc++.h>

using namespace std;

bool checkWin(vector<char>& board, char player) {
    vector<vector<int>> winPatterns = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Horizontal
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Vertical
        {0, 4, 8}, {2, 4, 6}             // Diagonal
    };
    for (const auto& pattern : winPatterns) {
        bool win = true;
        for (int pos : pattern) {
            if (board[pos] != player) {
                win = false;
                break;
            }
        }
        if (win) {
            return true;
        }
    }
    return false;
}

bool isMovesLeft(const vector<char>& board) {
    for (char cell : board) {
        if (cell == '-') {
            return true;
        }
    }
    return false;
}

int evaluate(const vector<char>& b, char player, char opponent) {
    // Checking for Rows, Columns, and Diagonals for X or O victory.
    for (int i = 0; i < 3; ++i) {
        if (b[i * 3] == b[i * 3 + 1] && b[i * 3 + 1] == b[i * 3 + 2]) { // Rows
            if (b[i * 3] == player) return 10;
            else if (b[i * 3] == opponent) return -10;
        }
        if (b[i] == b[i + 3] && b[i + 3] == b[i + 6]) { // Columns
            if (b[i] == player) return 10;
            else if (b[i] == opponent) return -10;
        }
    }
    if ((b[0] == b[4] && b[4] == b[8]) || (b[2] == b[4] && b[4] == b[6])) { // Diagonals
        if (b[4] == player) return 10;
        else if (b[4] == opponent) return -10;
    }
    return 0; // If none of them have won then return 0
}

int minimax(vector<char>& board, int depth, bool isMax, char player, char opponent) {
    int score = evaluate(board, player, opponent);

    // If Maximizer or Minimizer has won the game
    if (score == 10 || score == -10) return score;

    // If there are no more moves and no winner then it is a tie
    if (!isMovesLeft(board)) return 0;

    // If this maximizer's move
    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 9; ++i) {
            if (board[i] == '-') {
                board[i] = player;
                best = max(best, minimax(board, depth + 1, !isMax, player, opponent));
                board[i] = '-';
            }
        }
        return best;
    }
    // If this minimizer's move
    else {
        int best = 1000;
        for (int i = 0; i < 9; ++i) {
            if (board[i] == '-') {
                board[i] = opponent;
                best = min(best, minimax(board, depth + 1, !isMax, player, opponent));
                board[i] = '-';
            }
        }
        return best;
    }
}

pair<int, int> findBestMove(vector<char>& board, char player, char opponent) {
    int bestVal = -1000;
    pair<int, int> bestMove = {-1, -1};

    // Traverse all cells, evaluate minimax function for all empty cells, and return the cell with the optimal value.
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            // Check if cell is empty
            if (board[i * 3 + j] == '-') {
                // Make the move
                board[i * 3 + j] = player;
                // Compute evaluation function for this move
                int moveVal = minimax(board, 0, false, player, opponent);
                // Undo the move
                board[i * 3 + j] = '-';
                // If the value of the current move is more than the best value, then update best
                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

void printBoard(const vector<char>& board) {
    cout << " 0 1 2" << endl;
    for (int i = 0; i < 3; ++i) {
        cout << i << " ";
        for (int j = 0; j < 3; ++j) {
            cout << board[i * 3 + j] << " ";
        }
        cout << endl;
    }
    cout<<endl;
}

int main() {
    vector<char> board(9, '-'); // Initial board
    char player = 'x', opponent = 'o';
    bool currentPlayer = true; // true for player 'x', false for player 'o'

    cout << "Welcome to Tic Tac Toe!" << endl;

    while (true) {
        printBoard(board);

        if (checkWin(board, player)) {
            cout << "Player " << (currentPlayer ? "X" : "O") << " wins!" << endl;
            break;
        } else if (!isMovesLeft(board)) {
            cout << "Game drawn!" << endl;
            break;
        } else {
            if (currentPlayer) {
                pair<int, int> bestMove = findBestMove(board, player, opponent);
                board[bestMove.first * 3 + bestMove.second] = player;
                cout << "AI Move:" << endl;
            } else {
                int row, col;
                cout << "Your Move: ";
                cin >> row >> col;
                if (board[row * 3 + col] != '-') {
                    cout << "Invalid Move!" << endl;
                    continue;
                }
                board[row * 3 + col] = opponent;
            }
            currentPlayer = !currentPlayer;
        }
    }

    printBoard(board);

    return 0;
}
