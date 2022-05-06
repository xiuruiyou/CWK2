#include <stdio.h>
#include <intrin.h>
#include "evolution.h"

int world[5][5] = {{0, 0, 0, 0, 0},
                   {0, 0, 1, 0, 0},
                   {1, 0, 1, 0, 0},
                   {0, 1, 1, 0, 0},
                   {0, 0, 0, 0, 0}};

world_size initialize() {
    FILE *file = fopen("data.txt", "r");
    world_size size;
    int heng = 0;
    int shu = 0;
    int flag;
    if (file == NULL) {
        printf("Open error!");
//        return;
    }
//    else {
//        printf("successfully open!\n");
//    }
    while (!feof(file)) {
        flag = fgetc(file);
        if (flag == '\n') {
            shu++;
//            heng++;
        } else if (flag == ',') {
            heng++;
        }
    }
    shu++;
//    heng++;
//    printf("%d\n", shu);
    heng /= shu;
//    printf("%d\n", heng);
    fclose(file);
    size.heng=heng;
    size.shu=shu;
    return size;
}

void change() {
    int count;
    int test[5][5];//change
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            count = world[i - 1][j - 1] + world[i - 1][j] + world[i - 1][j + 1] + world[i][j - 1] +
                    world[i][j + 1] +
                    world[i + 1][j - 1] + world[i + 1][j] + world[i + 1][j + 1];
            switch (count) {
                case 2:
                    test[i][j] = world[i][j];
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
    memcpy(world, test, sizeof(int) * 5 * 5);
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            printf("%d ", test[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}