//
// Created by 86186 on 2022/5/14.
//
#ifndef EVOLUTION_C_SDL_H
#define EVOLUTION_C_SDL_H

#include <stdbool.h>
#include<SDL2/SDL.h>
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();
bool GameOverPhoto();
int GameOver();
//Frees media and shuts down SDL
void close();

int cover();
int board();
bool mousePosition(int a, int b, int c, int d);
#endif //EVOLUTION_C_SDL_H
