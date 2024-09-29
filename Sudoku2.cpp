#include<vector>
#include<iostream>
#include<cmath>
#include<chrono>

using namespace std;

///-------------------------------------------------------------------------
// Function to take input for the Sudoku board
void take_input(vector<vector<int>> &sudoku_board){
    for(int i = 0 ; i < 9 ; i++){
        vector<int> v ;
        for(int j = 0 ; j < 9 ; j++){
            int a ;
            // Read input and check for valid numbers (1-9 or -1 for empty)
            cin >> a ;
            if((a > 0 && a < 10) || a == -1) 
                v.push_back(a) ;
            else {
                cout << "Invalid Input, put a valid number" << endl ;
                j--; // Decrement j to re-input the current cell
            }
        }
        sudoku_board.push_back(v); // Add the row to the Sudoku board
    }
}


//-----------------------------------------------------------------------
// Function to print the Sudoku board
void print_sudoku(vector<vector<int>> v){
    for(int i = 0 ; i < 9 ; i++){
        for(int j = 0 ; j < 9 ; j++) 
            cout << v[i][j] << " " ; // Print each number with space
        cout << endl; // New line after each row
    }
}


//--------------------------------------------------------------------
// Function to count the number of empty cells (marked as -1)
int n_empty_cells(vector<vector<int>> sudoku_board){
    int count = 0 ;
    for(int i = 0 ; i < 9 ; i++){
        for(int j = 0 ; j < 9 ; j++){
            if(sudoku_board[i][j] == -1) 
                count++; // Increment count for each empty cell
        }
    }
    return count ; // Return total empty cells
}


//---------------------------------------------------------------------
// Function to find the first empty cell in the Sudoku board
vector<int> empty_place(vector<vector<int>> v){
    vector<int> ep; // Vector to store row and column indices of the empty cell
    for(int i = 0 ; i < 9 ; i++){
        for(int j = 0 ; j < 9 ; j++){
            if(v[i][j] == -1){ // Check for empty cell
                ep.push_back(i); // Store row index
                ep.push_back(j); // Store column index
                return ep; // Return the first found empty cell
            }
        }
    }
    // If no empty cells found, return (-1, -1)
    if(ep.size() != 2) {
        ep.push_back(-1) ;
        ep.push_back(-1) ;
    }
    return ep; // Return vector with indices of the empty cell or (-1, -1)
}


//-----------------------------------------------------------------
// Function to check if placing a number (guess) in a cell is safe
bool safe_to_place(vector<vector<int>> &sudoku_board, int guess, int row, int col){
    // Check if guess is in the same column
    for(int i = 0; i < 9; i++){
        if(sudoku_board[i][col] == guess) 
            return false; // Unsafe if guess already exists in column
    }

    // Check if guess is in the same row
    for(int i = 0; i < 9; i++){
        if(sudoku_board[row][i] == guess) 
            return false; // Unsafe if guess already exists in row
    }

    // Check 3x3 grid for the guess
    int row_start = (row / 3) * 3, col_start = (col / 3) * 3;
    for(int i = row_start; i < row_start + 3; i++){
        for(int j = col_start; j < col_start + 3; j++){
            if(sudoku_board[i][j] == guess) 
                return false; // Unsafe if guess already exists in 3x3 grid
        }
    }

    return true; // Safe to place guess
}

// Function to get the numbers possible in a Cell
vector<int> get_numbers(vector<vector<int>> sudoku_board , int r , int c){
    vector<int> v ;
    for(int g = 1 ; g <= 9 ; g++){
        if(safe_to_place(sudoku_board , g , r , c)){
            v.push_back(g) ;
        }
    }
    return v ;
}

//-----------------------------------------------------------------------------
// Naked Singles
int naked_singles(vector<vector<int>> sudoku_board){
    int n = 0 ; 
    bool in_row = false , in_col = false , in_grid = false ;
    for(int r = 0 ; r < 9 ; r++){
        for(int c = 0 ; c < 9 ; c++){
            
            // Check Row
            for(int i = 0 ; i < 9 ; i++){
                if(sudoku_board[r][i] == sudoku_board[r][c]){
                    in_row = true ;
                    break ;
                }
            }
            
            // Check Column
            for(int i = 0 ; i < 9 && !in_row ; i++){
                if(sudoku_board[i][c] == sudoku_board[r][c]){
                    in_col = true ;
                    break ;
                }
            }

            // Check Grid
            int rs = (r/3)*3 , cs = (c/3)*3 ;
            for(int i = rs ; i < rs+3 && !in_col && !in_row ; i++){
                for(int j = cs ; j < cs+3 ; j++){
                    if(sudoku_board[i][j] == sudoku_board[r][c]){
                        in_grid = true ;
                        break ;
                    }
                }
            }

            if(!in_col && !in_grid && !in_row) n++ ;

        }
    }
    return n ;
}

// Naked Doubles
int naked_doubles(vector<vector<int>> sudoku_board){
    int count = 0 ;
    for(int r = 0 ; r < 9 ; r++){
        for(int c = 0 ; c < 9 ; c++){
            if(sudoku_board[r][c] == -1){
                vector<int> possible_numbers = get_numbers(sudoku_board , r , c) ;
                if(possible_numbers.size() == 2) count++ ;
            }
        }
    }
    return count ;
}


// Naked Triples
int naked_triples(vector<vector<int>> sudoku_board){
    int count = 0 ;
    for(int r = 0 ; r < 9 ; r++){
        for(int c = 0 ; c < 9 ; c++){
            if(sudoku_board[r][c] == -1){
                vector<int> possible_numbers = get_numbers(sudoku_board , r , c) ;
                if(possible_numbers.size() == 3) count++ ;
            }
        }
    }
    return count ;
}

// Hidden Singles
int hidden_singles(vector<vector<int>> sudoku_board){
    int count = 0 ;

    for(int g = 1 ; g < 10 ; g++){
        // Check Row-Wise hidden singles
        for(int r = 0 ; r <  9 ; r++){
            int g_possible = 0 ;
            for(int c = 0 ; c < 9 ; c++){
                if(safe_to_place(sudoku_board , g , r , c) && sudoku_board[r][c] == -1) g_possible++ ;
            }
            if(g_possible == 1) count++ ;
        }

        // Check Column-Wise hidden singles
        for(int c = 0 ; c < 9 ; c++){
            int g_possible = 0 ;
            for(int r = 0 ; r < 9 ; r++){
                if(safe_to_place(sudoku_board , g , r , c) && sudoku_board[r][c] == -1) g_possible++ ;
            }
            if(g_possible == 1) count++ ;
        }

        // Check Grid-Wise hidden singles
        for(int grid_r = 0 ; grid_r < 3 ; grid_r++){
            for(int grid_c = 0 ; grid_c < 3 ; grid_c++){
                int g_possible = 0 ;
                for(int r = grid_r ; r < 3*grid_r+3 ; r++){
                    for(int c = grid_c ; c < 3*grid_c+3 ; c++){
                        if(safe_to_place(sudoku_board , g , r , c) && sudoku_board[r][c] == -1) g_possible++ ;
                    }
                }
                if(g_possible == 1) count++ ;
            }
        }

    }
    return count ; 
}

// Hidden Doubles
int hidden_doubles(vector<vector<int>> sudoku_board){
    int count = 0 ;

    for(int g1 = 1 ; g1 < 10 ; g1++){
        for(int g2 = g1+1 ; g2 < 10 ; g2++){
            // Check Row-Wise hidden doubles
            for(int r = 0 ; r < 9 ; r++){
                int gpair_possible = 0 ;
                for(int c = 0 ; c < 9 ; c++){
                    if(safe_to_place(sudoku_board , g1 , r , c) && safe_to_place(sudoku_board , g2 , r , c) && sudoku_board[r][c] == -1){
                        gpair_possible++ ;
                    }
                }
                if(gpair_possible == 2) count++ ;
            }

            // Check Column-Wise Hidden doubles
            for(int c = 0 ; c < 9 ; c++){
                int gpair_possible = 0 ;
                for(int r = 0 ; r < 9 ; r++){
                    if(safe_to_place(sudoku_board , g1 , r , c) && safe_to_place(sudoku_board , g2 , r , c) && sudoku_board[r][c] == -1){
                        gpair_possible++ ;
                    }
                }
                if(gpair_possible == 2) count++ ;
            }

            // Check Grid-Wise Hidden doubles
            for(int grid_row = 0 ; grid_row < 3 ; grid_row++){
                for(int grid_col = 0 ; grid_col < 3 ; grid_col++){
                    int gpair_possible = 0 ;
                    for(int r = grid_row*3 ; r < grid_row*3+3 ; r++){
                        for(int c = grid_col*3 ; c < grid_col*3+3 ; c++){
                            if(safe_to_place(sudoku_board , g1 , r , c) && safe_to_place(sudoku_board , g2 , r ,c) && sudoku_board[r][c] == -1){
                                gpair_possible++ ;
                            }
                        }
                    }
                    if(gpair_possible == 2) count++ ;
                }
            }
        }

    }
    return count ;
}

// Hidden Triples
int hidden_triples(vector<vector<int>> sudoku_board){
    int count = 0 ;
    for(int g1 = 1 ; g1 < 10 ; g1++){
        for(int g2 = g1+1 ; g2 < 10 ; g2++){
            for(int g3 = g2+1 ; g3 < 10 ; g3++){
                // Row-Wise hidden triples
                for(int r = 0 ; r < 9 ; r++){
                    int gtriple_possible = 0 ;
                    for(int c = 0 ; c < 9 ; c++){
                        if(safe_to_place(sudoku_board , g1 , r , c) && safe_to_place(sudoku_board , g2 , r , c) && safe_to_place(sudoku_board , g3 , r , c) && sudoku_board[r][c] == -1){
                            gtriple_possible++ ;
                        }
                    }
                    if(gtriple_possible == 3) count++ ;
                }

                // Column-Wise hidden triples
                for(int c = 0 ; c < 9 ; c++){
                    int gtriple_possible = 0 ;
                    for(int r = 0 ; r < 9 ; r++){
                        if(safe_to_place(sudoku_board , g1 , r , c) && safe_to_place(sudoku_board , g2 , r , c) && safe_to_place(sudoku_board , g3 , r , c) && sudoku_board[r][c] == -1){
                            gtriple_possible++ ;
                        }
                    }
                    if(gtriple_possible == 3) count++ ;
                }

                // Grid-Wise hidden triples
                for(int grid_r = 0 ; grid_r < 3 ; grid_r++){
                    for(int grid_c = 0 ; grid_c < 3 ; grid_c++){
                        int gtriple_possible = 0 ;
                        for(int r = grid_r*3 ; r < grid_r*3 + 3 ; r++){
                            for(int c = grid_c*3 ; c < grid_c*3 + 3 ; c++){
                                if(safe_to_place(sudoku_board , g1 , r , c) && safe_to_place(sudoku_board , g2 , r , c) && safe_to_place(sudoku_board , g3 , r , c) && sudoku_board[r][c] == -1){
                                    gtriple_possible++ ;
                                }
                            }
                        }
                        if(gtriple_possible == 3) count++ ;
                    }
                }
            }
        }
    }

    return count ;
}

//-----------------------------------------------------------------------------
// Function to count valid options for a specific cell
int count_valid_options(vector<vector<int>> sudoku_board, int r, int c){
    int n = 0; // Count of valid options
    for(int i = 1; i <= 9; i++){
        if(safe_to_place(sudoku_board, i, r, c)){
            n++; // Increment count for each valid option
        }
    }
    return n; // Return the count of valid options
}


//------------------------------------------------------------------------------
// Function to solve the Sudoku puzzle using backtracking
bool solve_sudoku(vector<vector<int>> &sudoku_board){
    bool sudoku_solved = false; // Flag to check if Sudoku is solved
    
    // Find the first empty place
    vector<int> Empty_Place = empty_place(sudoku_board);
    int r = Empty_Place[0], c = Empty_Place[1];

    if(r == -1) 
        sudoku_solved = true; // Sudoku is solved if no empty place is found
    else {

        // Try guessing numbers from 1 to 9
        for(int guess = 1; guess < 10; guess++){
            if(safe_to_place(sudoku_board, guess, r, c)){ // Check if guess is safe
                sudoku_board[r][c] = guess; // Place the guess
                if(solve_sudoku(sudoku_board)){ // Recursive call
                    return true; // If solved, return true
                }
            }
        }
        sudoku_board[r][c] = -1; // Reset the cell if no guess works
    }

    // Print Sudoku board if solved
    if(sudoku_solved){
        print_sudoku(sudoku_board);
        return true; // Return true if Sudoku is solved
    } else {
        return false; // Return false if not solved
    }
}

// Main function
int main() { 
    vector<vector<int>> sudoku_board; // 2D vector to represent the Sudoku board
    
    // Taking Input
    take_input(sudoku_board);

    // Number of Empty Cells
    int n_empty = n_empty_cells(sudoku_board);
    cout << "Number of Empty Cells in the Sudoku: " << n_empty << endl ;
    
    // Timer Start
    auto start = chrono::high_resolution_clock::now();

    // Naked Singles
    int n_naked_singles = naked_singles(sudoku_board) ;
    cout << "Number of Naked Singles Initially: " <<  n_naked_singles << endl ;

    // Naked Doubles
    int n_naked_doubles = naked_doubles(sudoku_board) ;
    cout << "Number of Naked Doubles Initially: " << n_naked_doubles << endl ;

    // Naked Doubles
    int n_naked_triples = naked_triples(sudoku_board) ;
    cout << "Number of Naked Doubles Initially: " << n_naked_triples << endl ;

    // Hidden Singles
    int n_hidden_singles = hidden_singles(sudoku_board) ;
    cout << "Number of Hidden Singles Initially: " << n_hidden_singles << endl ;

     // Hidden Doubles
    int n_hidden_doubles = hidden_doubles(sudoku_board) ;
    cout << "Number of Hidden Doubles Initially: " << n_hidden_doubles << endl ;

     // Hidden Triples
    int n_hidden_triples = hidden_triples(sudoku_board) ;
    cout << "Number of Hidden Triples Initially: " << n_hidden_triples << endl ;

    // Solve Sudoku
    if(solve_sudoku(sudoku_board)){
        double difficulty = -3.0*n_naked_singles - 2.0*n_naked_doubles - 1.0*n_naked_triples - 1.0*n_hidden_singles + 1.0*n_hidden_doubles + 5.0*n_hidden_triples - 4.0*n_empty ;
        cout << "The difficulty Score is: " << difficulty << endl ;

        // Normalize the Difficulty Score (Calculation done in the 'Difficulty Analyze Data.xlsx' file)
        double normalized_difficulty = (difficulty-(-3.89))/160.45 ;
        cout << "The Normalized Difficulty Score is: " << normalized_difficulty << endl ;

        if(normalized_difficulty < -0.95){
            cout << "The given Sudoku Puzzle is EASY" << endl ; 
        }
        else if(normalized_difficulty < -0.65){
            cout << "The given Sudoku Puzzle is MEDIUM" << endl ;
        }
        else if(normalized_difficulty < -0.1){
            cout << "The given Sudoku Puzzle is HARD" << endl ;
        }

        else if(normalized_difficulty < 0.1){
            cout << "The given Sudoku Puzzle is EXPERT" << endl ;
        }
        else if(normalized_difficulty < 1.2){
            cout << "The given Sudoku Puzzle is MASTER" << endl ;
        }
        else {
            cout << "The given Sudoku Puzzle is EXTREME" << endl ;
        }
    } 
    
    else {
        cout << "Invalid Sudoku" << endl; // If the Sudoku is unsolvable
    }

    // End time
    auto end = chrono::high_resolution_clock::now();

    // Calculate elapsed time
    chrono::duration<double, milli> elapsed = end - start; // Duration in milliseconds
    cout << "Time taken to solve the Sudoku: " << elapsed.count() << " ms" << endl;

    return 0; 
}
