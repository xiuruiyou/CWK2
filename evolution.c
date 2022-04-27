//
// Created by 86186 on 2022/4/27.
//

#include <stdio.h>
#include <intrin.h>

void change() {
    int count;
    int world[5][5] = {{0, 0, 0, 0, 0},
                       {0, 0, 1, 0, 0},
                       {1, 0, 1, 0, 0},
                       {0, 1, 1, 0, 0},
                       {0, 0, 0, 0, 0}};
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            printf("%d ", world[i][j]);
        }
        printf("\n");
    }
    printf("\n");
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