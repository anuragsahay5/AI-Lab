#include <iostream>
#include <vector>

using namespace std;

int n;
vector<vector<int>> board;
vector<vector<vector<int>>> solutions;

bool isSafe(int row, int col) {
    // Check if there is a queen in the same column
    for (int i = 0; i < row; ++i) {
        if (board[i][col] == 1) {
            return false;
        }
    }

    // Check upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    // Check upper right diagonal
    for (int i = row, j = col; i >= 0 && j < n; --i, ++j) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    return true;
}

void solveQueens(int row) {
    if (row == n) {
        solutions.push_back(board);
        return;
    }

    for (int col = 0; col < n; ++col) {
        if (isSafe(row, col)) {
            board[row][col] = 1;
            solveQueens(row + 1);
            board[row][col] = 0; // backtrack
        }
    }
}

void printSolution(int index) {
    if (index >= 0 && index < solutions.size()) {
        for (const auto& row : solutions[index]) {
            for (int val : row) {
                cout << val << " ";
            }
            cout << endl;
        }
    } else {
        cout << "Invalid index." << endl;
    }
}

int main() {
    cout << "Enter the size of the chessboard (n x n): ";
    cin >> n;
    if(n<=3){
        cout<<"No Possible Solution Exists\n";
        return 0;
    }
    board.resize(n, vector<int>(n, 0));
    solveQueens(0);

    cout << "Number of solutions: " << solutions.size() << endl;

    cout << "Enter the index of the solution to print (0-" << solutions.size() - 1 << "): ";
    int index;
    cin >> index;

    cout << "Solution " << index << ":" << endl;
    printSolution(index);

    return 0;
}
