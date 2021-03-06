#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "sdl.h"
#include "generate.h"

//Screen dimension constants
const int SCREEN_WIDTH = 761;
const int SCREEN_HEIGHT = 661;

//The window we'll be rendering to
SDL_Window *gWindow = NULL;

//The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface *gHelloWorld = NULL;

bool init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        //Create the window
        gWindow = SDL_CreateWindow("Loading for games", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            //Get the window's surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

bool loadMedia() {
    //Loading success flag
    bool success = true;

    //Load splash image
    gHelloWorld = SDL_LoadBMP("image/cover.bmp");
    if (gHelloWorld == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", "image/cover.bmp", SDL_GetError());
        success = false;
    }

    return success;
}

bool GameOverPhoto() {
    //Loading success flag
    bool success = true;

    //Load splash image
    gHelloWorld = SDL_LoadBMP("image/GameOver.bmp");
    if (gHelloWorld == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", "image/GameOver.bmp", SDL_GetError());
        success = false;
    }

    return success;
}

void close() {
    //Deallocate surface
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

int cover() {
    //Start up SDL and create window
    if (!init()) {
        printf("Failed to initialize!\n");
        return -1;
    } else {
        //Load media
        if (!loadMedia()) {
            printf("Failed to load media!\n");
            return -1;
        } else {
            //Apply the image
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

            //Update the surface
            SDL_UpdateWindowSurface(gWindow);

            //Wait two seconds
            SDL_Delay(1500);
        }
    }
    //Free resources and close SDL
    close();

    return 0;
}

int GameOver() {
    //Start up SDL and create window
    if (!init()) {
        printf("Failed to initialize!\n");
        return -1;
    } else {
        //Load media
        if (!GameOverPhoto()) {
            printf("Failed to load media!\n");
            return -1;
        } else {
            //Apply the image
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

            //Update the surface
            SDL_UpdateWindowSurface(gWindow);

            //Wait two seconds
            SDL_Delay(3000);
        }
    }
    //Free resources and close SDL
    close();
    return 0;
}

int board(char *userFileName) {
    char USER1[100];
    strcpy(USER1, userFileName);
    int column = getSize(USER1).column;
    int row = getSize(USER1).row;
    double width = 600.0 / column;
    double height = 600.0 / row;
    SDL_Window *sdl_window;
    SDL_Renderer *renderer;
    int quit = false;
    SDL_Event event;
    // 0 init sdl
    SDL_Init(SDL_INIT_VIDEO);

    //create window
    sdl_window = SDL_CreateWindow("TheGameOfLife",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  600,
                                  600,
                                  SDL_WINDOW_SHOWN);
    //create renderer
    renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_SOFTWARE);

    //set renderer color (set background color  Blue)
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);

    //clear color
    SDL_RenderClear(renderer);

    //background grey
    SDL_Rect rect1 = {0, 0, 600, 600};
    SDL_RenderDrawRect(renderer, &rect1);
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect1);

    // black and white
    FILE *file = fopen(USER1, "r");
    if (file == NULL) {
        printf("The file of nowState does not exist.\n");
        return -1;
    }
    int w[row][column];
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            fscanf(file, "%d,", &w[i][j]);
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
        fscanf(file, "\n");
    }
    fclose(file);

    // show window
    SDL_RenderPresent(renderer);

    int x = 0;
    int y = 0;
    int xPosition = 0;
    int yPosition = 0;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_BACKSPACE) {
                    quit = true;
                }
            }
            if (event.type == SDL_MOUSEMOTION) {
                SDL_GetMouseState(&x, &y);
                xPosition = x / width;
                yPosition = y / height;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_RIGHT) {
                    SDL_Rect rect5 = {xPosition * width, yPosition * height, width - 2.0, height - 2.0};
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                    SDL_RenderFillRect(renderer, &rect5);
                    SDL_RenderPresent(renderer);
                    w[yPosition][xPosition] = 0;
                } else if (event.button.button == SDL_BUTTON_LEFT) {
                    SDL_Rect rect5 = {xPosition * width, yPosition * height, width - 2.0, height - 2.0};
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                    SDL_RenderFillRect(renderer, &rect5);
                    SDL_RenderPresent(renderer);
                    w[yPosition][xPosition] = 1;
                }
            }
        }
    }

    FILE *file11 = fopen("test.txt", "w");
    if (file11 == NULL) {
        printf("The file of nowState does not exist.\n");
        return -1;
    }
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            fprintf(file11, "%d,",w[i][j]);
        }
        if(i!=row-1){
            fprintf(file11,"\n");
        }
    }
    fclose(file11);

    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (sdl_window) {
        SDL_DestroyWindow(sdl_window);
    }
    SDL_Quit();
    return 0;
}



