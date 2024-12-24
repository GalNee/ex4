/******************
Name: Gal Neeman
ID: 331981365
Assignment: ex4
*******************/
#include <stdio.h>
#include <string.h>

#define PYRAMID_SIZE 5
#define BRACKETS 4
#define DIRECTIONS 2
#define MAX_WORD_SIZE 16


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

float calc_total_weight(int row, int col, float pyr[PYRAMID_SIZE][PYRAMID_SIZE]) {
    if (row == 0) return pyr[0][0];
    //if the person is on the edges it needs to calculate the total weight of only 1 person instead of 2
    if (col == 0) return pyr[row][col] + calc_total_weight(row - 1, col, pyr) / 2;
    if (col == row) return pyr[row][col] + calc_total_weight(row - 1, col - 1, pyr) / 2;

    return pyr[row][col] + (calc_total_weight(row - 1, col - 1, pyr) + calc_total_weight(row - 1, col, pyr)) / 2;
}

void task2_human_pyramid() {
    float pyramid[PYRAMID_SIZE][PYRAMID_SIZE];
    printf("Please enter the weights of the cheerleaders:\n");
    for (int i = 0; i < PYRAMID_SIZE; i++) {
        for (int j = 0; j <= i; j++) {
            scanf(" %f", &pyramid[i][j]);
            if (pyramid[i][j] < 0) {
                printf("Negative weights are not supported.\n");
                return;
            }
        }
    }
    printf("\n");
    for (int i = 0; i < PYRAMID_SIZE; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%.02f ", calc_total_weight(i, j, pyramid));
        }
        printf("\n");
    }
}

//finds the index of a value in an array, if it's not in the array it returns -1;
int find_index(int size, char arr[size], char value, int counter) {
    if (counter == size) return -1;
    if (arr[counter] == value) return counter;
    return find_index(size, arr, value, counter + 1);
}

int is_patenthesis_valid(char chr, char starting_brackets[BRACKETS], char ending_brackets[BRACKETS],
                         int opening_bracket_index) {
    //if the line ends and there is an unclosed bracket returns false
    if (chr == '\n') return opening_bracket_index == -1;

    //if there is a closing bracket...
    if (find_index(BRACKETS, ending_brackets, chr, 0) != -1)
        //if no opening bracket before or the wrong type returns false
        return opening_bracket_index != -1 && chr == ending_brackets[opening_bracket_index];

    //input another char
    char next_chr;
    scanf("%c", &next_chr);

    int starting_index = find_index(BRACKETS, starting_brackets, chr, 0);
    if (starting_index != -1)
        //checking the inner brackets and only then the outer ones(uses * instead of && to read to whole input)
        return is_patenthesis_valid(next_chr, starting_brackets, ending_brackets, starting_index) *
               is_patenthesis_valid('a', starting_brackets, ending_brackets, opening_bracket_index);

    return is_patenthesis_valid(next_chr, starting_brackets, ending_brackets, opening_bracket_index);
}

void task3_parenthesis_validator() {
    char chr, starting_brackets[] = "<([{", ending_brackets[] = ">)]}";
    printf("Please enter a term for validation:\n");
    scanf(" %c", &chr);
    int isBalanced = is_patenthesis_valid(chr, starting_brackets, ending_brackets, -1);
    if (isBalanced) printf("The parentheses are balanced correctly.\n");
    else printf("The parentheses are not balanced correctly.\n");
}

//a function that returns true if there is another queen in the same column
int is_a_queen_in_column(int size, char solution[size][size], int row, int col) {
    if (row == size) return 0;
    if (solution[row][col] == 'X') return 1;
    return is_a_queen_in_column(size, solution, row + 1, col);
}

//a function that returns true if there is a queen adjacent to the queen the program wants to place(sorry, it's ugly)
int is_a_queen_adjacent(int size, char solution[size][size], int row, int col) {
    if (row == 0 && col == 0) return solution[row + 1][col + 1] == 'X';
    if (row == size - 1 && col == size - 1) return solution[row - 1][col - 1] == 'X';
    if (row == 0 && col == size - 1) return solution[row + 1][col - 1] == 'X';
    if (row == size - 1 && col == 0) return solution[row - 1][col + 1] == 'X';
    if (col == size - 1) return solution[row - 1][col - 1] == 'X' || solution[row + 1][col - 1] == 'X';
    if (col == 0) return solution[row + 1][col + 1] == 'X' || solution[row - 1][col + 1] == 'X';
    if (row == size - 1) return solution[row - 1][col - 1] == 'X' || solution[row - 1][col + 1] == 'X';
    if (row == 0) return solution[row + 1][col + 1] == 'X' || solution[row + 1][col - 1] == 'X';
    return solution[row - 1][col + 1] == 'X' || solution[row - 1][col - 1] == 'X' || solution[row + 1][col - 1] == 'X'
           ||
           solution[row + 1][col + 1] == 'X';
}

//a function that returns true if a queen can be placed in a specific place based on the rules of the game
int can_place_queen(int size, int grid[size][size], char solution[size][size], int row, int col, int colors[size]) {
    return !is_a_queen_in_column(size, solution, 0, col) && colors[grid[row][col]] == 0 &&
           !is_a_queen_adjacent(size, solution, row, col) && solution[row][col] == 0;
}

//the recursive function that finds the solution
int solution_queens_battle(int size, int grid[size][size], char solution[size][size], int row, int col,
                           int colors[size]) {
    if (row == size) return 1;

    /*if there is no place for a queen in a row it will return to the previous row and if there is no previous row it
     will just return 0*/
    if (col == size) return 0;
    //place a queen if it can and mark that the color is occupied
    if (can_place_queen(size, grid, solution, row, col, colors)) {
        solution[row][col] = 'X';
        colors[grid[row][col]] = 1;
        if (solution_queens_battle(size, grid, solution, row + 1, 0, colors)) return 1;
        solution[row][col] = '\0';
        colors[grid[row][col]] = 0;
    }
    return solution_queens_battle(size, grid, solution, row, col + 1, colors);
}


//changes the grid from a char array to an int array with numbers from 0 to size-1
void get_int_grid(int size, char grid[size][size], int intGrid[size][size], char colors[size], int row, int col) {
    if (row == size) return;
    if (col == size) get_int_grid(size, grid, intGrid, colors, row + 1, 0);
    else {
        intGrid[row][col] = find_index(size, colors, grid[row][col], 0);
        get_int_grid(size, grid, intGrid, colors, row, col + 1);
    }
}

void init_solution_grid(int size, char solution[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            solution[i][j] = '\0';
        }
    }
}

void printBoard(int size, char solution[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (solution[i][j] == '\0') printf("*");
            else printf("%c", solution[i][j]);
        }
        printf("\n");
    }
}

void task4_queens_battle() {
    int size, counter = 0;
    printf("Please enter the board dimensions:\n");
    scanf(" %d", &size);
    char grid[size][size], colors[size], solution[size][size];
    int intGrid[size][size], colorOcc[size];
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
        printBoard(size, solution);
    } else printf("This puzzle cannot be solved.\n");
}

struct crossword_instructions {
    int row;
    int col;
    int length;
    int direction[DIRECTIONS];
};

//a function to place a word in a specific place
void place_word(int row, int col, int length, int direction[2], int size, char word[length],
                char solution[size][size], int counter) {
    if (counter == length) return;
    solution[row][col] = word[counter];
    place_word(row + direction[1], col + direction[0], length, direction, size, word, solution, counter + 1);
}

//a function to check if it's possible to place a word in a specific place
int can_place_word(int row, int col, int requiredLength, int length, int direction[2], int size, char word[length],
                   char solution[size][size], int wordIndex, int numOfSlots, int usedWords[numOfSlots], int counter) {
    if (counter == length) return 1;
    if (requiredLength != length || usedWords[wordIndex] != 0 ||
        (solution[row][col] != '\0' && solution[row][col] != word[counter]))
        return 0;
    return can_place_word(row + direction[1], col + direction[0], requiredLength, length, direction, size, word,
                          solution, wordIndex, numOfSlots, usedWords, counter + 1);
}

//a function to remove a word
void remove_word(int row, int col, int length, int direction[2], int size,
                 char solution[size][size], int counter) {
    if (counter == length) return;
    solution[row][col] = '\0';
    remove_word(row + direction[1], col + direction[0], length, direction, size, solution, counter + 1);
}

//a function to print the crossword
void print_crossword(int size, char solution[size][size]) {
    for (int i = 0; i < size; i++) {
        printf("|");
        for (int j = 0; j < size; j++) {
            if (solution[i][j] == '\0') printf(" # |");
            else printf(" %c |", solution[i][j]);
        }
        printf("\n");
    }
}

//the recursive function to solve the crossword(pretty similar to the queen's battle function)
int crossword_solver(int size, int numOfWords, int numOfSlots, char solution[size][size],
                     char dictionary[numOfWords][15], int counter, int usedWords[numOfSlots],
                     int wordIndex, struct crossword_instructions gridInstructions[numOfSlots]) {
    if (counter == numOfSlots) return 1;
    if (wordIndex == numOfWords) return 0;
    if (can_place_word(gridInstructions[counter].row, gridInstructions[counter].col,
                       gridInstructions[counter].length,
                       strlen(dictionary[wordIndex]), gridInstructions[counter].direction, size,
                       dictionary[wordIndex], solution, wordIndex, numOfSlots, usedWords,
                       0)) {
        usedWords[wordIndex] = 1;
        place_word(gridInstructions[counter].row,
                   gridInstructions[counter].col, gridInstructions[counter].length, gridInstructions[counter].direction,
                   size,
                   dictionary[wordIndex], solution, 0);
        if (crossword_solver(size, numOfWords, numOfSlots, solution, dictionary, counter + 1, usedWords, 0,
                             gridInstructions))
            return 1;
        remove_word(gridInstructions[counter].row, gridInstructions[counter].col,
                    gridInstructions[counter].length,
                    gridInstructions[counter].direction, size, solution, 0);
        usedWords[wordIndex] = 0;
    }
    return crossword_solver(size, numOfWords, numOfSlots, solution, dictionary, counter, usedWords, wordIndex + 1,
                            gridInstructions);
}


void task5_crossword_generator() {
    int size, numOfSlots, numOfWords;
    printf("Please enter the dimensions of the crossword grid:\n");
    scanf(" %d", &size);
    printf("Please enter the number of slots in the crossword:\n");
    scanf(" %d", &numOfSlots);
    char solution[size][size];
    init_solution_grid(size, solution);
    struct crossword_instructions gridInstructions[numOfSlots];
    printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
    for (int i = 0; i < numOfSlots; i++) {
        char dir;
        scanf(" %d %d %d %c", &gridInstructions[i].row, &gridInstructions[i].col, &gridInstructions[i].length,
              &dir);
        int direction[] = {0, 0};
        if (dir == 'V') direction[1] = 1;
        else if (dir == 'H') direction[0] = 1;
        gridInstructions[i].direction[0] = direction[0];
        gridInstructions[i].direction[1] = direction[1];
    }
    printf("Please enter the number of words in the dictionary:\n");
    while (scanf(" %d", &numOfWords) && numOfWords < numOfSlots) {
        printf("The dictionary must contain at least %d words. Please enter a valid dictionary size:\n", numOfSlots);
    }
    char dictionary[numOfWords][MAX_WORD_SIZE];
    for (int i = 0; i < numOfWords; i++) {
        for (int j = 0; j < MAX_WORD_SIZE; j++) {
            dictionary[i][j] = '\0';
        }
    }
    int usedWords[numOfWords];
    for (int i = 0; i < numOfWords; i++) {
        usedWords[i] = 0;
    }
    printf("Please enter the words for the dictionary:\n");
    for (int i = 0; i < numOfWords; i++) {
        scanf(" %s", &dictionary[i]);
    }
    if (crossword_solver(size, numOfWords, numOfSlots, solution, dictionary, 0, usedWords, 0, gridInstructions)) {
        print_crossword(size, solution);
    } else printf("This crossword cannot be solved.\n");
}
