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

int main()
{
    int task = -1;
    do
    {
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");

        if (scanf("%d", &task))
        {
            switch (task)
            {
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
        }
        else
        {
            scanf("%*s");
        }

    } while (task != 6);
}

int findRobotPaths(int row, int col) {
    //if it's on the edge there is only 1 direction to go
    if (row == 0 || col == 0) return 1;
    return findRobotPaths(row-1, col) + findRobotPaths(row, col-1);
}

void task1_robot_paths()
{
    int col,row, numOfPaths = 0;
    printf("Please enter the coordinates of the robot (column, row):\n");
    scanf(" %d %d",&col,&row);
    if (col >= 0 && row >= 0) numOfPaths = findRobotPaths(row, col);
    printf("The total number of paths the robot can take to reach home is: %d\n", numOfPaths);
}

float calcTotalWeight(int row, int col, float pyr[5][5]) {
    if (row == 0) return pyr[0][0];
    if (col == 0) return pyr[row][col] + calcTotalWeight(row-1, col, pyr)/2;
    if (col == row) return pyr[row][col] + calcTotalWeight(row-1, col - 1, pyr)/2;
    return pyr[row][col] + (calcTotalWeight(row-1, col-1, pyr) + calcTotalWeight(row-1, col, pyr))/2;
}

void task2_human_pyramid() {
    float pyramid[5][5];
    printf("Please enter the weights of the cheerleaders:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= i ; j++) {
            scanf(" %f",&pyramid[i][j]);
            if (pyramid[i][j] < 0) {
                printf("Negative weights are not supported.\n");
                return;
            }
        }
    }
    printf("\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= i ; j++) {
            printf("%.02f ", calcTotalWeight(i, j, pyramid));
        }
        printf("\n");
    }



}

void task3_parenthesis_validator()
{
    // Todo
}

void task4_queens_battle()
{
    // Todo
}

void task5_crossword_generator()
{
    // Todo
}