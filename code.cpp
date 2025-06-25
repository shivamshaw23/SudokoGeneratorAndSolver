#include <bits/stdc++.h>
using namespace std;

const int N = 9;

void print_grid(int grid[N][N]) {
    for(int i = 0; i < N; i++) {
        if(i % 3 == 0 && i != 0) {
            cout << "-------------------------------" <<endl;
        }
        for(int j = 0; j < N; j++) {
            if(j % 3 == 0 && j != 0) {
                cout << " | ";
            }
            if(grid[i][j] == 0) {
                cout << " . ";
            } else {
                cout << " " << grid[i][j] << " ";
            }
        }
        cout <<endl;
    }
}

bool is_safe(int grid[N][N], int row, int col, int num) {
    for(int d = 0; d < N; d++) {
        if(grid[row][d] == num) return false;
    }
    for(int r = 0; r < N; r++) {
        if(grid[r][col] == num) return false;
    }
    int start_row = row - row % 3;
    int start_col = col - col % 3;
    for(int r = 0; r < 3; r++) {
        for(int d = 0; d < 3; d++) {
            if(grid[start_row + r][start_col + d] == num) return false;
        }
    }
    return true;
}

bool solve_sudoku(int grid[N][N]) {
    for(int row = 0; row < N; row++) {
        for(int col = 0; col < N; col++) {
            if(grid[row][col] == 0) {
                for(int num = 1; num <= N; num++) {
                    if(is_safe(grid, row, col, num)) {
                        grid[row][col] = num;
                        if(solve_sudoku(grid)) {
                            return true;
                        }
                        grid[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void generate_sudoku(int solution[N][N], int puzzle[N][N], int holes) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            solution[i][j] = 0;
        }
    }
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine engine(seed);
    for(int i = 0; i < 3; i++) {
        shuffle(nums.begin(), nums.end(), engine);
        int idx = 0;
        for(int row = i * 3; row < i * 3 + 3; row++) {
            for(int col = i * 3; col < i * 3 + 3; col++) {
                solution[row][col] = nums[idx++];
            }
        }
    }
    solve_sudoku(solution);
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            puzzle[i][j] = solution[i][j];
        }
    }
    int removed = 0;
    while(removed < holes) {
        int row = uniform_int_distribution<int>{0, N-1}(engine);
        int col = uniform_int_distribution<int>{0, N-1}(engine);
        if(puzzle[row][col] != 0) {
            puzzle[row][col] = 0;
            removed++;
        }
    }
}

bool is_grid_complete(int grid[N][N]) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(grid[i][j] == 0) return false;
        }
    }
    return true;
}

bool check_solution(int user[N][N], int solution[N][N]) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(user[i][j] != solution[i][j]) return false;
        }
    }
    return true;
}

void user_solve(int puzzle[N][N], int user[N][N], int solution[N][N]) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            user[i][j] = puzzle[i][j];
        }
    }
    while(true) {
        cout << "\nCurrent puzzle:\n";
        print_grid(user);
        int row, col, num;
        cout << "Enter row (1-9, 0 to check solution): ";
        cin >> row;
        if(row == 0) {
            if(is_grid_complete(user)) {
                if(check_solution(user, solution)) {
                    cout << "Congratulations! You solved the puzzle correctly!"<<endl;
                } else {
                    cout << "Sorry, your solution is incorrect."<<endl;
                }
            } else {
                cout << "Puzzle is not complete yet."<<endl;
            }
            cout << "Do you want to continue solving? (y/n): ";
            char choice;
            cin >> choice;
            if(choice != 'y' && choice != 'Y') break;
            continue;
        }
        row--;
        if(row < 0 || row >= N) {
            cout << "Invalid row. Try again."<<endl;
            continue;
        }
        cout << "Enter column (1-9): ";
        cin >> col;
        col--;
        if(col < 0 || col >= N) {
            cout << "Invalid column. Try again."<<endl;
            continue;
        }
        if(puzzle[row][col] != 0) {
            cout << "This cell is fixed and cannot be changed."<<endl;
            continue;
        }
        cout << "Enter number (1-9): ";
        cin >> num;
        if(num < 1 || num > 9) {
            cout << "Invalid number. Try again."<<endl;
            continue;
        }
        if(is_safe(user, row, col, num)) {
            user[row][col] = num;
        } else {
            cout << "Invalid move. Number conflicts with row, column, or subgrid."<<endl;
        }
    }
}

int main() {
    int solution[N][N] = {0};
    int puzzle[N][N] = {0};
    int user[N][N] = {0};
    bool puzzle_generated = false;
    while(true) {
        cout << "\nSudoku Game Menu:"<<endl;
        cout << "1. Generate new Sudoku puzzle"<<endl;
        cout << "2. Show solution"<<endl;
        cout << "3. Solve the puzzle"<<endl;
        cout << "4. Exit"<<endl;
        cout << "Enter your choice (1-4): ";
        int choice;
        cin >> choice;
        switch(choice) {
            case 1:
                generate_sudoku(solution, puzzle, 45);
                puzzle_generated = true;
                cout << "\nGenerated Sudoku puzzle:"<<endl;
                print_grid(puzzle);
                break;
            case 2:
                if(!puzzle_generated) {
                    cout << "No puzzle generated yet. Please generate a puzzle first."<<endl;
                } else {
                    cout << "\nSolution:"<<endl;
                    print_grid(solution);
                }
                break;
            case 3:
                if(!puzzle_generated) {
                    cout << "No puzzle generated yet. Please generate a puzzle first."<<endl;
                } else {
                    user_solve(puzzle, user, solution);
                }
                break;
            case 4:
                cout << "Exiting program."<<endl;
                return 0;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 4."<<endl;
        }
    }
    return 0;
}