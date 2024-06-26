#include <climits>
#include <iostream>
#include <vector>

using namespace std;

const int ROWS = 6;
const int COLS = 7;
const int MAX_DEPTH = 5; // Maximum depth to search in Mini-Max algorithm

// Function to print the current board
void printBoard(vector<vector<char>> &board) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if the move is valid
bool isValidMove(vector<vector<char>> &board, int col) {
    return col >= 0 && col < COLS && board[0][col] == '-';
}

// Function to make a move
void makeMove(vector<vector<char>> &board, int col, char player) {
    for (int i = ROWS - 1; i >= 0; --i) {
        if (board[i][col] == '-') {
            board[i][col] = player;
            break;
        }
    }
}

// Function to check if the board is full
bool isBoardFull(vector<vector<char>> &board) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (board[i][j] == '-') {
                return false;
            }
        }
    }
    return true;
}

// Check if there is a winner
bool checkWinner(vector<vector<char>> &board, char player) {
    // Horizontally
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j <= COLS - 4; ++j) {
            if (board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player && board[i][j + 3] == player) {
                return true;
            }
        }
    }
    // Vertically
    for (int j = 0; j < COLS; ++j) {
        for (int i = 0; i <= ROWS - 4; ++i) {
            if (board[i][j] == player && board[i + 1][j] == player && board[i + 2][j] == player && board[i + 3][j] == player) {
                return true;
            }
        }
    }
    // Diagonally (bottom-left to top-right)
    for (int i = 0; i <= ROWS - 4; ++i) {
        for (int j = 0; j <= COLS - 4; ++j) {
            if (board[i][j] == player && board[i + 1][j + 1] == player && board[i + 2][j + 2] == player && board[i + 3][j + 3] == player) {
                return true;
            }
        }
    }
    // Diagonally (top-left to bottom-right)
    for (int i = 3; i < ROWS; ++i) {
        for (int j = 0; j <= COLS - 4; ++j) {
            if (board[i][j] == player && board[i - 1][j + 1] == player && board[i - 2][j + 2] == player && board[i - 3][j + 3] == player) {
                return true;
            }
        }
    }
    return false;
}

// Evaluate the board
int evaluateBoard(vector<vector<char>> &board) {
    if (checkWinner(board, 'X'))
        return 1000; // Maximizer wins
    else if (checkWinner(board, 'O'))
        return -1000; // Minimizer wins
    else
        return 0; // Draw
}

// Mini-Max function with Alpha-Beta pruning
int miniMax(vector<vector<char>> &board, int depth, bool isMaximizer, int alpha, int beta) {
    int score = evaluateBoard(board);
    if (depth == MAX_DEPTH || score != 0) {
        return score;
    }
    if (isBoardFull(board))
        return 0; // Draw
    if (isMaximizer) {
        int maxScore = INT_MIN;
        for (int col = 0; col < COLS; ++col) {
            if (isValidMove(board, col)) {
                makeMove(board, col, 'X');
                int currentScore = miniMax(board, depth + 1, false, alpha, beta);
                maxScore = max(maxScore, currentScore);
                alpha = max(alpha, currentScore);
                board[ROWS - 1][col] = '-'; // Undo the move
                if (beta <= alpha)
                    break; // Beta cut-off
            }
        }
        return maxScore;
    } else {
        int minScore = INT_MAX;
        for (int col = 0; col < COLS; ++col) {
            if (isValidMove(board, col)) {
                makeMove(board, col, 'O');
                int currentScore = miniMax(board, depth + 1, true, alpha, beta);
                minScore = min(minScore, currentScore);
                beta = min(beta, currentScore);
                board[ROWS - 1][col] = '-'; // Undo the move
                if (beta <= alpha)
                    break; // Alpha cut-off
            }
        }
        return minScore;
    }
}

// Function to find the best move using Mini-Max with Alpha-Beta pruning
int findBestMove(vector<vector<char>> &board) {
    int bestMove = -1;
    int bestScore = INT_MIN;
    int alpha = INT_MIN;
    int beta = INT_MAX;
    for (int col = 0; col < COLS; ++col) {
        if (isValidMove(board, col)) {
            makeMove(board, col, 'X');
            int currentScore = miniMax(board, 0, false, alpha, beta);
            if (currentScore > bestScore) {
                bestScore = currentScore;
                bestMove = col;
            }
            board[ROWS - 1][col] = '-'; // Undo the move
        }
    }
    return bestMove; // column number with bestScore
}

int main() {
    vector<vector<char>> board(ROWS, vector<char>(COLS, '-'));
    int movesCount = 0;
    while (true) {
        printBoard(board);
        // Player's turn
        int playerMove;
        cout << "Your turn! Enter column number (0-6): ";
        cin >> playerMove;
        if (isValidMove(board, playerMove)) {
            makeMove(board, playerMove, 'O');
            movesCount++;
            if (checkWinner(board, 'O')) {
                cout << "Congratulations! You win!" << endl;
                break;
            }
            if (isBoardFull(board)) {
                cout << "It's a draw!" << endl;
                break;
            }
        } else {
            cout << "Invalid move! Try again." << endl;
            continue;
        }
        // Computer's turn
        if (movesCount < ROWS * COLS) {
            int computerMove = findBestMove(board);
            makeMove(board, computerMove, 'X');
            cout << "AI's move: " << computerMove << endl;
            if (checkWinner(board, 'X')) {
                cout << "AI wins!" << endl;
                break;
            }
            if (isBoardFull(board)) {
                cout << "It's a draw!" << endl;
                break;
            }
        } else {
            cout << "It's a draw!" << endl;
            break;
        }
    }
    printBoard(board);
    return 0;
}
