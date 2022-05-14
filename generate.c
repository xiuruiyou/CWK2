#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generate.h"
#include "evolution.h"
#include "sdl.h"
int generateTxt(int row, int column, char *userFileName)
{
    char USER[100];
    strcpy(USER, userFileName);
    strcat(USER, "-nowState.txt");
    FILE *file = fopen(USER, "w");
    if(file==NULL){
        printf("Can't open the file.\n");
        return -1;
    }
    int cells;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            cells = rand()%2;
            fprintf(file,"%d,",cells);
        }
        if(i!=row-1){
            fprintf(file,"\n");
        }
    }
    fclose(file);
    return 0;
}

world_size getSize(char *userFileName1)
{
    char USER1[100];
    strcpy(USER1, userFileName1);
    FILE *file = fopen(USER1, "r");
    world_size size;
    int column = 0;
    int row = 0;
    world_size error;
    int error1 = -1;
    int error2 = -1;
    error.row = error1;
    error.column = error2;
    char flag;
    if (file == NULL) {
        printf("Open error!");
        return error;
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

void newGame(char *userFileName)
{
    char USER[100];
    strcpy(USER, userFileName);
    int height, width, times;
    printf("Please enter the height of world: ");
    scanf("%d", &height);
    printf("Please enter the width of world: ");
    scanf("%d", &width);
    generateTxt(height,width,USER);
    printf("Please enter the times of evolution: ");
    scanf("%d", &times);
    getchar();
    printf("\n\n");
    change(times,USER);
//    board(USER);
}

void OldGame(char *userFileName)
{
    char USER[100];
    strcpy(USER, userFileName);
    int times;
    printf("Please enter the times of evolution: ");
    scanf("%d", &times);
    getchar();
    printf("\n\n");
    GoOnGame(times,USER);
}

int over(char *userFileName, int row, int column)
{
    char USER1[100];
    strcpy(USER1, userFileName);
    FILE *file = fopen(USER1, "r");
    if (file == NULL) {
        printf("The file of nowState does not exist.\n");
        return -1;
    }
    int count = 0;
    int w[row][column];
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            fscanf(file, "%d,", &w[i][j]);
            if (w[i][j] == 1){
                count++;
            }
        }
        fscanf(file, "\n");
    }
    if (count==0){
        return 0;
    } else return 1;
}
