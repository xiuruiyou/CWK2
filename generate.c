#include<stdio.h>
#include <stdlib.h>
#include "generate.h"
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
