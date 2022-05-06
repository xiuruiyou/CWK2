#include<stdio.h>
#include "evolution.h"
#include<SDL2/SDL.h>
int main(int argc, char* argv[])
{
    int heng,shu;
    heng = initialize().heng;
    shu = initialize().shu;
    int world[heng][shu];
    printf("%d,%d\n",heng,shu);
    FILE *file = fopen("data.txt","r");
    if (file==NULL){
        printf("The file does not exist.\n");
        return -1;
    }
    for (int i = 0; i < shu; ++i) {
        for (int j = 0; j < heng; ++j) {
            fscanf(file,"%d,",&world[i][j]);
        }
        fscanf(file,"\n");
    }
    fclose(file);
    for (int i = 0; i < shu; ++i) {
        for (int j = 0; j < heng; ++j) {
            printf("%d ", world[i][j]);
        }
        printf("\n");
    }
//    initialize();
//    change();
//    change();
//    change();
    return 0;
}