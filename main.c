#include "interface.h"
#include "sdl.h"
#include <SDL2/SDL.h>
int main(int argc, char* argv[])
{
//    cover();
    interface();
    return 0;
}

//#include <stdio.h>
//#include <SDL2/SDL.h>
//#include <stdbool.h>
//int main(int argc, char* argv[])
//{
//
//    SDL_Init(SDL_INIT_VIDEO);
//    SDL_Window* window = SDL_CreateWindow("Tutorial", SDL_WINDOWPOS_UNDEFINED,
//                                          SDL_WINDOWPOS_UNDEFINED,
//                                          600, 600, SDL_WINDOW_SHOWN);
//    SDL_Surface* surface = SDL_GetWindowSurface(window);
//    SDL_Surface* picture1 = SDL_LoadBMP( "image/white.bmp" );
//    SDL_Surface* picture2 = SDL_LoadBMP( "image/black.bmp" );
//    SDL_Event event;
//
//
//
//    bool quit = false;
//    SDL_Rect rect = {200,200,100,100};
//
//    //事件驱动
//    while (quit == false)
//    {
//        while (SDL_PollEvent(&event))
//        {
//            //点击关闭按钮事件
//            if (SDL_QUIT == event.type)
//            {
//                printf("hello world");
//                quit = true;
//
//            }else if(SDL_MOUSEBUTTONDOWN == event.type)
//            {
//                //鼠标按下事件
//                printf("click");
//                if (SDL_BUTTON_LEFT == event.button.button)
//                {
//                    printf("left");
//                    SDL_BlitSurface(picture1,NULL, surface,&rect);
//                    SDL_UpdateWindowSurface(window);
//                    //--
//                }
//                else if (SDL_BUTTON_RIGHT == event.button.button)
//                {
//                    printf("right");
//                    SDL_BlitSurface(picture2, NULL, surface, &rect);
//                    SDL_UpdateWindowSurface(window);
//                }
//            }
//        }
//    }
//
//    SDL_FreeSurface(surface);
//    SDL_FreeSurface(picture1);
//    SDL_FreeSurface(picture2);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//}



