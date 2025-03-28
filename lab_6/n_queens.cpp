#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cout;
using std::cin;
using std:: endl;

bool IsSafe(const vector<int>& board, int curr_row, int curr_col) {
    for (int i = 0; i < board.size(); ++i) {
        int placed_row = board[i];
        int placed_col = i + 1;
        if (abs(placed_row - curr_row) == abs(placed_col - curr_col)) {
            return false;
        }
    }
    return true;
}

void NQueenUtil(int col, int n, vector<int>* board, vector<vector<int>>* res, vector<bool>* visited) {
    if (col > n) {
        res->push_back(*board);
        return;
    }

    for (int row = 1; row <= n; ++row) {
        if (!(*visited)[row]) {
            if (IsSafe(*board, row, col)) {
                (*visited)[row] = true;
                board->push_back(row);
                NQueenUtil(col + 1, n, board, res, visited);
                board->pop_back();
                (*visited)[row] = false;
            }
        }
    }
}

vector<vector<int>> SolveNQueens(int n) {
    vector<vector<int>> res;
    vector<int> board;
    vector<bool> visited(n + 1, false);
    NQueenUtil(1, n, &board, &res, &visited);
    return res;
}

int main() {
    int kBoardSize;
    cin >> kBoardSize;
    vector<vector<int>> solutions = SolveNQueens(kBoardSize);
    for (const auto& solution : solutions) {
        cout << "[";
        for (int j = 0; j < kBoardSize; ++j) {
            cout << solution[j];
            if (j != kBoardSize - 1) {
                cout << " ";
            }
        }
        cout << "]\n";
    }
    cout << "total solutions: " << solutions.size() << endl;
    return 0;
}