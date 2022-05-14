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

//Frees media and shuts down SDL
void close();

int cover();
int board();
#endif //EVOLUTION_C_SDL_H