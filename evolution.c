#include <stdio.h>
#include <intrin.h>
#include "evolution.h"


world_size getSize() {
    FILE *file = fopen("data.txt", "r");
    world_size size;
    int column = 0;
    int row = 0;
    char flag;
    if (file == NULL) {
        printf("Open error!");
    }
    while (!feof(file)) {
        flag = fgetc(file);
        if (flag == '\n') {
            row++;
        } else if (flag == ',') {
            column++;
        }
    }
    row++;
    column /= row;
    fclose(file);
    size.column = column;
    size.row = row;
    return size;
}

void change(int times) {
    int column, row;
    column = getSize().column;
    row = getSize().row;
    int w[row][column];
    printf("%d,%d\n", row, column);
    FILE *history = fopen("history.txt", "a");
    if (history == NULL) {
        printf("The file of history does not exist.\n");
        return;
    }
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("The file does not exist.\n");
        return;
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
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            printf("%d ", w[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int k = 0; k < times; ++k) {
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
                printf("%d ", test[i][j]);
                fprintf(history,"%d,",test[i][j]);
            }
            printf("\n");
            fprintf(history,"\n");
        }
        printf("\n");
        fprintf(history,"\n");
    }
}