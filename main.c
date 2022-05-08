#include<stdio.h>
#include "evolution.h"
#include<SDL2/SDL.h>
#include "generate.h"
int main(int argc, char* argv[])
{
    printf("\n");
    generateTxt(5,5);
    change(2);
    return 0;
}