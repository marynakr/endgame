#ifndef HEAD_H
#define HEAD_H

#include <unistd.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
//#include <SDL2/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2/SDL_timer.h>

typedef struct s_param {
    SDL_Window *win;
    SDL_Renderer *rend;

} t_App;


#define WINDOW_WIDTH (1280)
#define WINDOW_HEIGHT (1024)

void mx_printerr(const char *s);
int mx_strlen(const char *s);

void init_win(t_App *app);


#endif

