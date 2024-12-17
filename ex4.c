/******************
Name: Gal Neeman
ID: 331981365
Assignment: ex4
*******************/
#include <stdio.h>
#include <string.h>

void task1_robot_paths();

void task2_human_pyramid();

void task3_parenthesis_validator();

void task4_queens_battle();

void task5_crossword_generator();

int main() {
    int task = -1;
    do {
        printf("Choose an option:\n"
            "1. Robot Paths\n"
            "2. The Human Pyramid\n"
            "3. Parenthesis Validation\n"
            "4. Queens Battle\n"
            "5. Crossword Generator\n"
            "6. Exit\n");

        if (scanf("%d", &task)) {
            switch (task) {
                case 6:
                    printf("Goodbye!\n");
                    break;
                case 1:
                    task1_robot_paths();
                    break;
                case 2:
                    task2_human_pyramid();
                    break;
                case 3:
                    task3_parenthesis_validator();
                    break;
                case 4:
                    task4_queens_battle();
                    break;
                case 5:
                    task5_crossword_generator();
                    break;
                default:
                    printf("Please choose a task number from the list.\n");
                    break;
            }
        } else {
            scanf("%*s");
        }
    } while (task != 6);
}

int findRobotPaths(int row, int col) {
    //if it's on the edge there is only 1 direction to go
    if (row == 0 || col == 0) return 1;
    return findRobotPaths(row - 1, col) + findRobotPaths(row, col - 1);
}

void task1_robot_paths() {
    int col, row, numOfPaths = 0;
    printf("Please enter the coordinates of the robot (column, row):\n");
    scanf(" %d %d", &col, &row);
    if (col >= 0 && row >= 0) numOfPaths = findRobotPaths(row, col);
    printf("The total number of paths the robot can take to reach home is: %d\n", numOfPaths);
}

float calc_total_weight(int row, int col, float pyr[5][5]) {
    if (row == 0) return pyr[0][0];
    //if the person is on the edges it needs to calculate the total weight of only 1 person instead of 2
    if (col == 0) return pyr[row][col] + calc_total_weight(row - 1, col, pyr) / 2;
    if (col == row) return pyr[row][col] + calc_total_weight(row - 1, col - 1, pyr) / 2;

    return pyr[row][col] + (calc_total_weight(row - 1, col - 1, pyr) + calc_total_weight(row - 1, col, pyr)) / 2;
}

void task2_human_pyramid() {
    float pyramid[5][5];
    printf("Please enter the weights of the cheerleaders:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= i; j++) {
            scanf(" %f", &pyramid[i][j]);
            if (pyramid[i][j] < 0) {
                printf("Negative weights are not supported.\n");
                return;
            }
        }
    }
    printf("\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%.02f ", calc_total_weight(i, j, pyramid));
        }
        printf("\n");
    }
}

void task3_parenthesis_validator() {
    // Todo
}

//a function that returns true if there is another queen in the same column
int is_a_queen_in_column(int size, int solution[size][size], int row, int col) {
    if (row == size) return 0;
    if (solution[row][col] == 1) return 1;
    return is_a_queen_in_column(size, solution, row + 1, col);
}

//a function that returns true if there is a queen adjacent to the queen the program wants to place(sorry, it's ugly)
int is_a_queen_adjacent(int size, int solution[size][size], int row, int col) {
    if (row == 0 && col == 0) return solution[row + 1][col + 1] == 1;
    if (row == size - 1 && col == size - 1) return solution[row - 1][col - 1] == 1;
    if (col == size - 1) return solution[row - 1][col - 1] == 1 || solution[row + 1][col - 1] == 1;
    if (col == 0) return solution[row + 1][col + 1] == 1 || solution[row - 1][col + 1] == 1;
    if (row == size - 1) return solution[row - 1][col - 1] == 1 || solution[row - 1][col + 1] == 1;
    if (row == 0) return solution[row + 1][col + 1] == 1 || solution[row + 1][col - 1] == 1;
    return solution[row - 1][col + 1] == 1 || solution[row - 1][col - 1] == 1 || solution[row + 1][col - 1] == 1 ||
           solution[row + 1][col + 1] == 1;
}

//a function that returns true if a queen can be placed in a specific place based on the rules of the game
int can_place_queen(int size, int grid[size][size], int solution[size][size], int row, int col, int colors[size]) {
    return !is_a_queen_in_column(size, solution, 0, col) && colors[grid[row][col]] == 0 &&
        !is_a_queen_adjacent(size, solution, row, col) && solution[row][col] == 0;
}

//a function that removes the last queen placed and marks it so the program doesn't repeat the same place
void remove_previous_queen(int size, int grid[size][size],int solution[size][size], int row, int col, int colors[size]) {
    if (col == size || row == 0) return;
    solution[row][col] = 0;
    if (solution[row-1][col] == 1) {
        solution[row-1][col] = -1;
        colors[grid[row-1][col]] = 0;
    }
    remove_previous_queen(size, grid,solution, row, col+1, colors);
}

//the recursive function that finds the solution
int solution_queens_battle(int size, int grid[size][size], int solution[size][size], int row, int col,
    int colors[size]) {
    if (row == size) return 1;

    /*if there is no place for a queen in a row it will return to the previous row and if there is no previous row it
     will just return 0*/
    if (col == size) {
        remove_previous_queen(size, grid, solution, row, 0, colors);
        return 0;
    }
    //place a queen if it can and mark that the color is occupied
    if (can_place_queen(size, grid, solution, row, col, colors)) {
        solution[row][col] = 1;
        colors[grid[row][col]] = 1;
        if (solution_queens_battle(size, grid, solution, row + 1, 0, colors)) return 1;
    }
    return solution_queens_battle(size, grid, solution, row, col+1, colors);
}

//finds the index of a value in an array, if it's not in the array it returns -1;
int find_index(int size, char arr[size], char value, int counter) {
    if (counter == size) return -1;
    if (arr[counter] == value) return counter;
    return find_index(size, arr, value, counter + 1);
}

//changes the grid from a char array to an int array with numbers from 0 to size-1
void get_int_grid(int size, char grid[size][size], int intGrid[size][size], char colors[], int row, int col) {
    if (row == size) return;
    if (col == size) get_int_grid(size, grid, intGrid, colors, row + 1, 0);
    else {
        intGrid[row][col] = find_index(size, colors, grid[row][col], 0);
        get_int_grid(size, grid, intGrid, colors, row , col+1);
    }
}

void init_solution_grid(int size, int solution[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            solution[i][j] = 0;
        }
    }
}

void task4_queens_battle() {
    int size, counter = 0;
    printf("Please enter the board dimensions:\n");
    scanf(" %d", &size);
    char grid[size][size], colors[size];
    int intGrid[size][size], solution[size][size], colorOcc[size];
    init_solution_grid(size, solution);
    printf("Please enter the %d*%d puzzle board:\n", size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf(" %c", &grid[i][j]);
            //put the colors in an array
            if (find_index(size, colors, grid[i][j], 0) == -1) {
                colors[counter] = grid[i][j];
                counter++;
            }
        }
    }
    get_int_grid(size, grid, intGrid, colors, 0, 0);
    if (solution_queens_battle(size, intGrid, solution, 0, 0, colorOcc)) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (solution[i][j] == 1) printf("X");
                else printf("*");
            }
            printf("\n");
        }
    }
    else printf("This puzzle cannot be solved.\n");
}

void task5_crossword_generator() {
    // Todo
}
