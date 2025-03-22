#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

bool check_list(const vector<int>& subset) {
    for (int num = 1; num <= 9; ++num) {
        bool found = false;
        for (int i = 0; i < subset.size(); ++i) {
            if (subset[i] == num) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

bool place_check(const vector<vector<int>>& puzzle, int row, int col, int num) {
    // Check row
    for (int i = 0; i < 9; ++i) {
        if (puzzle[row][i] == num) {
            return false;
        }
    }

    // Check column
    for (int j = 0; j < 9; ++j) {
        if (puzzle[j][col] == num) {
            return false;
        }
    }

    // Check subgrid
    int startRow = row - (row % 3);
    int startCol = col - (col % 3);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (puzzle[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

bool backtrack_solve(vector<vector<int>>& puzzle, int row, int col) {
    if (row == 8 && col == 9) {
        return true;
    }

    if (col == 9) {
        row += 1;
        col = 0;
    }

    if (puzzle[row][col] != 0) {
        return backtrack_solve(puzzle, row, col + 1);
    }

    for (int entry = 1; entry <= 9; ++entry) {
        if (place_check(puzzle, row, col, entry)) {
            puzzle[row][col] = entry;
            if (backtrack_solve(puzzle, row, col + 1)) {
                return true;
            }
            puzzle[row][col] = 0;
        }
    }

    return false;
}

bool check_puzzle(const vector<vector<int>>& puzzle) {
    bool valid_sol = true;

    // Check rows
    for (const auto& row : puzzle) {
        if (!check_list(row)) {
            valid_sol = false;
        }
    }

    // Check columns
    for (int col = 0; col < 9; ++col) {
        vector<int> columns;
        for (int row = 0; row < 9; ++row) {
            columns.push_back(puzzle[row][col]);
        }
        if (!check_list(columns)) {
            valid_sol = false;
        }
    }

    // Check subgrids
    vector<vector<int>> subgrids(9);

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            int subgrid_index = (row / 3) * 3 + (col / 3);
            subgrids[subgrid_index].push_back(puzzle[row][col]);
        }
    }

    for (const auto& subgrid : subgrids) {
        if (!check_list(subgrid)) {
            valid_sol = false;
        }
    }

    return valid_sol;
}

void print_puzzle(const vector<vector<int>>& puzzle) {
    for (const auto& row : puzzle) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int>> puzzle = {
        {1, 7, 9, 0, 6, 4, 0, 0, 0},
        {4, 0, 0, 0, 1, 0, 0, 9, 5},
        {6, 0, 0, 9, 0, 0, 0, 7, 1},
        {3, 4, 6, 0, 0, 0, 0, 0, 2},
        {5, 0, 1, 0, 9, 0, 0, 6, 7},
        {0, 0, 0, 6, 3, 5, 0, 8, 0},
        {2, 0, 3, 7, 8, 0, 0, 0, 0},
        {0, 5, 7, 0, 4, 6, 2, 0, 0},
        {9, 6, 0, 2, 5, 3, 0, 1, 0}
    };

    // Start measuring time
    clock_t start_time = clock();

    backtrack_solve(puzzle, 0, 0);

    // End measuring time
    clock_t end_time = clock();

    // Check if the puzzle is solved and print the result
    if (check_puzzle(puzzle)) {
        cout << "Puzzle solved successfully!" << endl;
    } else {
        cout << "Puzzle is not solved correctly!" << endl;
    }

    // Print the solved puzzle
    print_puzzle(puzzle);

    // Print execution time in seconds
    double execution_time = double(end_time - start_time) / CLOCKS_PER_SEC;
    cout << "Execution time: " << execution_time << " seconds" << endl;

    return 0;
}
