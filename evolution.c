#include <stdio.h>
#include <intrin.h>
#include "evolution.h"
#include "generate.h"
#include "sdl.h"

//这个函数的功能有读取现在的状态并且录入历史文件，并且把每一次的变化写入历史文件。在次数用完时，再用最新的状态覆盖存放现在的状态的文件。
int change(int times, char *userFileName,int speed)
{
    int s = speed;
    char USER[100];
    strcpy(USER, userFileName);
    strcat(USER, "-History.txt");
    char USER1[100];
    strcpy(USER1, userFileName);
    strcat(USER1, "-nowState.txt");
    int column, row;
    column = getSize(USER1).column;
    row = getSize(USER1).row;
    int w[row][column];
//    printf("%d,%d\n", row, column);
    FILE *history = fopen(USER, "w"); //create the file of history file.
    if (history == NULL) {
        printf("The file of history does not exist.\n");
        return -1;
    }
    FILE *file = fopen(USER1, "r");
    if (file == NULL) {
        printf("The file of nowState does not exist.\n");
        return -1;
    }
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            fscanf(file, "%d,", &w[i][j]);
            fprintf(history, "%d,",w[i][j]);
        }
        fscanf(file, "\n");
        fprintf(history,"\n");
    }
    fprintf(history, "\n");
    fclose(file);
    board(USER1);

    //read the state of cells which is changed by click
    FILE *file12 = fopen("test.txt", "r");
    if (file12 == NULL) {
        printf("The file of nowState does not exist.\n");
        return -1;
    }
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            fscanf(file12, "%d,", &w[i][j]);
        }
        fscanf(file12, "\n");
    }
    fclose(file12);


    for (int k = 0; k < times; ++k) {
        FILE *file1 = fopen(USER1, "w");
        if (file1 == NULL) {
            printf("The file of nowState does not exist.\n");
            return -1;
        }
        int count;
        int test[row][column];//change
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                if (i == 0 && j == 0) {
                    count = w[i][j + 1] + w[i + 1][j] + w[i + 1][j + 1];
                } else if (i == 0 && j != 0 && j != column - 1) {
                    count = w[i][j - 1] + w[i][j + 1] + w[i + 1][j - 1] + w[i + 1][j] + w[i + 1][j + 1];
                } else if (i == 0 && j == column - 1) {
                    count = w[i][j - 1] + w[i + 1][j - 1] + w[i + 1][j];
                } else if (j == column - 1 && i != 0 && i != row - 1) {
                    count = w[i - 1][j - 1] + w[i - 1][j] + w[i][j - 1] + w[i + 1][j - 1] + w[i + 1][j];
                } else if (j == column - 1 && i == row - 1) {
                    count = w[i - 1][j - 1] + w[i - 1][j] + w[i][j - 1];
                } else if (i == row - 1 && j != 0 && j != column - 1) {
                    count = w[i - 1][j - 1] + w[i - 1][j] + w[i - 1][j + 1] + w[i][j - 1] + w[i][j + 1];
                } else if (i == row - 1 && j == 0) {
                    count = w[i - 1][j] + w[i - 1][j + 1] + w[i][j + 1];
                } else if (j == 0 && i != 0 && i != row - 1) {
                    count = w[i - 1][j] + w[i - 1][j + 1] + w[i][j + 1] + w[i + 1][j] + w[i + 1][j + 1];
                } else {
                    count = w[i - 1][j - 1] + w[i - 1][j] + w[i - 1][j + 1] + w[i][j - 1] + w[i][j + 1] +
                            w[i + 1][j - 1] + w[i + 1][j] + w[i + 1][j + 1];
                }
                switch (count) {
                    case 2:
                        test[i][j] = w[i][j];
                        break;
                    case 3:
                        test[i][j] = 1;
                        break;
                    default:
                        test[i][j] = 0;
                        break;
                }
            }
        }
        memcpy(w, test, sizeof(int) * column * row);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                fprintf(history,"%d,",test[i][j]);
                fprintf(file1,"%d,",test[i][j]);
            }
            fprintf(history,"\n");
            if(i!=row-1){
                fprintf(file1,"\n");
            }
        }
        fprintf(history,"\n");
        fclose(file1);
        autoBoard(USER1, s);
        if (over(USER1,row,column)==0){
            break;
        }
    }
    fclose(history);
    if (over(USER1,row,column)==0){
        GameOver();
    }
    return 0;
}

int GoOnGame(int times, char *userFileName, int speed)
{
    int s = speed;
    char USER[100];
    strcpy(USER, userFileName);
    strcat(USER, "-History.txt");
    char USER1[100];
    strcpy(USER1, userFileName);
    strcat(USER1, "-nowState.txt");
    int column, row;
    column = getSize(USER1).column;
    row = getSize(USER1).row;
    int w[row][column];
//    printf("%d,%d\n", row, column);
    FILE *history = fopen(USER, "a");
    if (history == NULL) {
        printf("The file of history does not exist.\n");
        return -1;
    }
    FILE *file = fopen(USER1, "r");
    if (file == NULL) {
        printf("The file does not exist.\n");
        return -1;
    }
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            fscanf(file, "%d,", &w[i][j]);
//            fprintf(history, "%d,",w[i][j]);
        }
        fscanf(file, "\n");
//        fprintf(history,"\n");
    }
//    fprintf(history, "\n");
    fclose(file);
    if (over(USER1,row,column)==0){
        printf("You must restart the game.\n");
        return 0;
    }
    board(USER1);

    //read the state of cells which is changed by click
    FILE *file12 = fopen("test.txt", "r");
    if (file12 == NULL) {
        printf("The file of nowState does not exist.\n");
        return -1;
    }
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            fscanf(file12, "%d,", &w[i][j]);
        }
        fscanf(file12, "\n");
    }
    fclose(file12);

    for (int k = 0; k < times; ++k) {
        FILE *file1 = fopen(USER1, "w");
        if (file1 == NULL) {
            printf("The file does not exist.\n");
            return -1;
        }
        int count;
        int test[row][column];//change
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                if (i == 0 && j == 0) {
                    count = w[i][j + 1] + w[i + 1][j] + w[i + 1][j + 1];
                } else if (i == 0 && j != 0 && j != column - 1) {
                    count = w[i][j - 1] + w[i][j + 1] + w[i + 1][j - 1] + w[i + 1][j] + w[i + 1][j + 1];
                } else if (i == 0 && j == column - 1) {
                    count = w[i][j - 1] + w[i + 1][j - 1] + w[i + 1][j];
                } else if (j == column - 1 && i != 0 && i != row - 1) {
                    count = w[i - 1][j - 1] + w[i - 1][j] + w[i][j - 1] + w[i + 1][j - 1] + w[i + 1][j];
                } else if (j == column - 1 && i == row - 1) {
                    count = w[i - 1][j - 1] + w[i - 1][j] + w[i][j - 1];
                } else if (i == row - 1 && j != 0 && j != column - 1) {
                    count = w[i - 1][j - 1] + w[i - 1][j] + w[i - 1][j + 1] + w[i][j - 1] + w[i][j + 1];
                } else if (i == row - 1 && j == 0) {
                    count = w[i - 1][j] + w[i - 1][j + 1] + w[i][j + 1];
                } else if (j == 0 && i != 0 && i != row - 1) {
                    count = w[i - 1][j] + w[i - 1][j + 1] + w[i][j + 1] + w[i + 1][j] + w[i + 1][j + 1];
                } else {
                    count = w[i - 1][j - 1] + w[i - 1][j] + w[i - 1][j + 1] + w[i][j - 1] + w[i][j + 1] +
                            w[i + 1][j - 1] + w[i + 1][j] + w[i + 1][j + 1];
                }
                switch (count) {
                    case 2:
                        test[i][j] = w[i][j];
                        break;
                    case 3:
                        test[i][j] = 1;
                        break;
                    default:
                        test[i][j] = 0;
                        break;
                }
            }
        }
        memcpy(w, test, sizeof(int) * column * row);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
//                printf("%d ", test[i][j]);
                fprintf(history,"%d,",test[i][j]);
                fprintf(file1,"%d,",test[i][j]);
            }
//            printf("\n");
            fprintf(history,"\n");
            if(i!=row-1){
                fprintf(file1,"\n");
            }
        }
//        printf("\n");
        fprintf(history,"\n");
        fclose(file1);
        autoBoard(USER1,s);
//        if (over(USER1,row,column)==0){
//            break;
//        }
    }
    fclose(history);
    if (over(USER1,row,column)==0){
        GameOver();
    }
    return 0;
}