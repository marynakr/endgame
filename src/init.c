#include "head.h"

void init_win(t_App *app) {
    // attempt to initialize graphics and timer system
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        mx_printerr("error initializing SDL:");
        mx_printerr(SDL_GetError());
        mx_printerr("\n");
        exit(1);      
    }

    app->win = SDL_CreateWindow("Hello, CS50!",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                WINDOW_WIDTH, WINDOW_HEIGHT,0);
    if (!app->win) {
        mx_printerr("error creating window:");
        mx_printerr(SDL_GetError());
        mx_printerr("\n");
        SDL_Quit();
	    exit(1);
    }

    // create a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    app->rend = SDL_CreateRenderer(app->win, -1, render_flags);
    if (!app->rend) {
      mx_printerr("error creating renderer:");
      mx_printerr(SDL_GetError());
      mx_printerr("\n");
      SDL_DestroyWindow(app->win);
      SDL_Quit();
      exit(1);
    }
}

