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
    FILE *file = fopen(USER, "w"); //create the file of nowState.
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

int generateAllDeadTxt(int row, int column, char *userFileName)
{
    char USER[100];
    strcpy(USER, userFileName);
    strcat(USER, "-nowState.txt");
    FILE *file = fopen(USER, "w"); //create the file of nowState.
    if(file==NULL){
        printf("Can't open the file.\n");
        return -1;
    }
    int cells;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            cells = 0;
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

void newRandomGame(char *userFileName)
{
    char USER[100];
    strcpy(USER, userFileName);
    int height, width, times, speed;
    bool h = false;
    bool w = false;
    bool s = false;
    bool t = false;
    while (!s){
        printf("Please the speed(between 500 and 5000): ");
        scanf("%d", &speed);
        getchar();
        if (speed > 5000){
            printf("Too slow.\n");
        } else if (speed < 500){
            printf("Too fast.\n");
        } else {
            s = true;
        }
    }
    while (!h){
        printf("Please enter the height of world(between 4 and 30): ");
        scanf("%d", &height);
        getchar();
        if (height > 30){
            printf("Too high.\n");
        } else if (height < 4){
            printf("Too low.\n");
        } else {
            h = true;
        }
    }
    while (!w){
        printf("Please enter the width of world(between 4 and 30): ");
        scanf("%d", &width);
        getchar();
        if (width > 30){
            printf("Too wide.\n");
        }else if (width < 4){
            printf("Too narrow.\n");
        }else{
            w = true;
        }
    }
    generateTxt(height,width,USER);
    while (!t){
        printf("Please enter the times(between 1 and 500): ");
        scanf("%d", &times);
        getchar();
        if (times > 500){
            printf("Too many.\n");
        } else if (times < 1){
            printf("Too little.\n");
        } else {
            t = true;
        }
    }
    printf("\n");
    change(times,USER, speed);
}

void newAllDeadGame(char *userFileName)
{
    char USER[100];
    strcpy(USER, userFileName);
    int height, width, times, speed;
    bool h = false;
    bool w = false;
    bool s = false;
    bool t = false;
    while (!s){
        printf("Please the speed(between 200 and 5000): ");
        scanf("%d", &speed);
        getchar();
        if (speed > 5000){
            printf("Too slow.\n");
        } else if (speed < 200){
            printf("Too fast.\n");
        } else {
            s = true;
        }
    }
    while (!h){
        printf("Please enter the height of world(between 4 and 30): ");
        scanf("%d", &height);
        getchar();
        if (height > 30){
            printf("Too high.\n");
        } else if (height < 4){
            printf("Too low.\n");
        } else {
            h = true;
        }
    }
    while (!w){
        printf("Please enter the width of world(between 4 and 30): ");
        scanf("%d", &width);
        getchar();
        if (width > 30){
            printf("Too wide.\n");
        }else if (width < 4){
            printf("Too narrow.\n");
        }else{
            w = true;
        }
    }
    generateAllDeadTxt(height,width,USER);
    while (!t){
        printf("Please enter the times(between 1 and 500): ");
        scanf("%d", &times);
        getchar();
        if (times > 500){
            printf("Too many.\n");
        } else if (times < 1){
            printf("Too little.\n");
        } else {
            t = true;
        }
    }
    printf("\n");
    change(times,USER, speed);
}

void OldGame(char *userFileName)
{
    char USER[100];
    strcpy(USER, userFileName);
    int times, speed;
    bool s = false;
    bool t = false;
    while (!s){
        printf("Please the speed(between 500 and 5000): ");
        scanf("%d", &speed);
        getchar();
        if (speed > 5000){
            printf("Too slow.\n");
        } else if (speed < 500){
            printf("Too fast.\n");
        } else {
            s = true;
        }
    }
    while (!t){
        printf("Please enter the times(between 1 and 500): ");
        scanf("%d", &times);
        getchar();
        if (times > 500){
            printf("Too many.\n");
        } else if (times < 1){
            printf("Too little.\n");
        } else {
            t = true;
        }
    }
    printf("\n");
    GoOnGame(times,USER,speed);
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
