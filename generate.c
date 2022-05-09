#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generate.h"
#include "evolution.h"
void generateTxt(int row, int column)
{
    FILE *file = fopen("data.txt", "w");
    if(file==NULL){
        printf("Can't open the file.\n");
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
    generateTxt(height,width);
    printf("Please enter the times of evolution: ");
    scanf("%d", &times);
    getchar();
    printf("\n\n");
    change(times,USER);
}
