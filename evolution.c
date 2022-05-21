#include <stdio.h>
#include <intrin.h>
#include "evolution.h"
#include "generate.h"
#include "sdl.h"

/*This function reads the current state and enters the history file, and writes each change to the
 history file. When the number of times runs out, the current state is overwritten with the latest state.*/
int change(int times, char *userFileName, int speed) {
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
            fprintf(history, "%d,", w[i][j]);
        }
        fscanf(file, "\n");
        fprintf(history, "\n");
    }
    fprintf(history, "\n");
    fclose(file);
    board(USER1);

    //read the state of cells which is changed by click
    FILE *file12 = fopen("test.txt", "r");
    if (file12 == NULL) {
        printf("The file of NowState does not exist.\n");
        return -1;
    }
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            fscanf(file12, "%d,", &w[i][j]);
        }
        fscanf(file12, "\n");
    }
    fclose(file12);

    double width = 600.0 / column;
    double height = 600.0 / row;
    SDL_Window *sdl_window;
    SDL_Renderer *renderer;
    SDL_Event event;
    // 0 init sdl
    SDL_Init(SDL_INIT_VIDEO);

    //create the window
    sdl_window = SDL_CreateWindow("TheGameOfLife",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  600,
                                  600,
                                  SDL_WINDOW_SHOWN);
    //create the renderer
    renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_SOFTWARE);

    //set renderer color (set background color)
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);

    //clear color
    SDL_RenderClear(renderer);


    int ccc = 0;
    int qwe;
    while (ccc < times) {

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_UP) {//Control the speed through the keyboard
                        if (qwe == 0)
                            qwe = 1;
                        else if (qwe == 1)
                            qwe = 0;
                        break;
                    } else if (event.key.keysym.sym == SDLK_RIGHT) {
                        if (s > 300) {
                            s = s - 100;
                        }
                        break;
                    } else if (event.key.keysym.sym == SDLK_LEFT) {
                        if (s < 10000) {
                            s = s + 100;
                        }
                        break;
                    } else {
                        break;
                    }
                case SDL_QUIT:
                    exit(0);
            }
        }

            int count;
            int test[row][column];//change
            FILE *file1 = fopen(USER1, "w");
            if (file1 == NULL) {
                printf("The file of nowState does not exist.\n");
                return -1;
            }
            //Count the number of living cells around each cell
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
            ccc++;
            for (int i = 0; i < row; ++i) {
                for (int j = 0; j < column; ++j) {
                    fprintf(history, "%d,", test[i][j]);
                    fprintf(file1, "%d,", test[i][j]);
                }
                fprintf(history, "\n");
                if (i != row - 1) {
                    fprintf(file1, "\n");
                }
            }
            fprintf(history, "\n");
            fclose(file1);

            //background grey
            SDL_Rect rect1 = {0, 0, 600, 600};
            SDL_RenderDrawRect(renderer, &rect1);
            SDL_SetRenderDrawColor(renderer, 128, 128, 128, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(renderer, &rect1);
            // black and white
            for (int i = 0; i < row; ++i) {
                for (int j = 0; j < column; ++j) {
                    SDL_Rect rect = {j * width, i * height, width - 2.0, height - 2.0};
                    SDL_RenderDrawRect(renderer, &rect);
                    if (w[i][j] == 0) {
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                        SDL_RenderFillRect(renderer, &rect);
                    } else if (w[i][j] == 1) {
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                        SDL_RenderFillRect(renderer, &rect);
                    }
                }
            }
            // show the renderer window
            SDL_RenderPresent(renderer);

            SDL_Delay(s);

        if (over(USER1, row, column) == 0) {
            break;
        }
    }

    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (sdl_window) {
        SDL_DestroyWindow(sdl_window);
    }
    SDL_Quit();

    fclose(history);

    if (over(USER1, row, column) == 0) {
        GameOver();
    }
    return 0;
}

//It is same as newGame function
int GoOnGame(int times, char *userFileName, int speed) {
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
        }
        fscanf(file, "\n");
    }
    fclose(file);
    if (over(USER1, row, column) == 0) {
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

    double width = 600.0 / column;
    double height = 600.0 / row;
    SDL_Window *sdl_window;
    SDL_Renderer *renderer;
    SDL_Event event;
    // 0 init sdl
    SDL_Init(SDL_INIT_VIDEO);

    //1 create window
    sdl_window = SDL_CreateWindow("TheGameOfLife",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  600,
                                  600,
                                  SDL_WINDOW_SHOWN);
    //2 create renderer
    renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_SOFTWARE);

    //3 set renderer color (set background color)
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);

    //4 clear color
    SDL_RenderClear(renderer);
    //background grey
    SDL_Rect rect1 = {0, 0, 600, 600};
    SDL_RenderDrawRect(renderer, &rect1);
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect1);

    int qwe = 0;
    for (int k = 0; k < times; ++k) {
        FILE *file1 = fopen(USER1, "w");
        if (file1 == NULL) {
            printf("The file does not exist.\n");
            return -1;
        }
        int count;
        int test[row][column];//change

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_p) {
                        if (qwe == 0)
                            qwe = 1;
                        else if (qwe == 1)
                            qwe = 0;
                        break;
                    } else if (event.key.keysym.sym == SDLK_RIGHT) {
                        if (s > 300) {
                            s = s - 100;
                        }
                        break;
                    } else if (event.key.keysym.sym == SDLK_LEFT) {
                        if (s < 10000) {
                            s = s + 100;
                        }
                        break;
                    } else {
                        break;
                    }
                case SDL_QUIT:
                    exit(0);
            }
        }

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
                fprintf(history, "%d,", test[i][j]);
                fprintf(file1, "%d,", test[i][j]);
            }
            fprintf(history, "\n");
            if (i != row - 1) {
                fprintf(file1, "\n");
            }
        }
        fprintf(history, "\n");
        fclose(file1);

        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                SDL_Rect rect = {j * width, i * height, width - 2.0, height - 2.0};
                SDL_RenderDrawRect(renderer, &rect);
                if (w[i][j] == 0) {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                    SDL_RenderFillRect(renderer, &rect);
                } else if (w[i][j] == 1) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
        }
        fclose(file);

        // show window
        SDL_RenderPresent(renderer);


        SDL_Delay(s);

    }
    fclose(history);
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (sdl_window) {
        SDL_DestroyWindow(sdl_window);
    }
    SDL_Quit();
    if (over(USER1, row, column) == 0) {
        GameOver();
    }
    return 0;
}