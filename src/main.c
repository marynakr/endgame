/**
 * hello7_mouse.c - the sprite follows the cursor, or is chased if you click
 */

// #include <stdio.h>
// #include <math.h>
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_timer.h>
// #include <SDL2/SDL_image.h>

#include "head.h"


// speed in pixels/second
#define SPEED (300)

int main(void)
{
    t_App app;

    init_win(&app);

    // load the image into memory using SDL_image library function
    SDL_Surface* surface = IMG_Load("rsc/animals/anim2.jpg");
    if (!surface)
    {
        printf("error creating surface\n");
        SDL_DestroyRenderer(app.rend);
        SDL_DestroyWindow(app.win);
        SDL_Quit();
        return 1;
    }

    // load the image data into the graphics hardware's memory
    SDL_Texture* tex = SDL_CreateTextureFromSurface(app.rend, surface);
    SDL_FreeSurface(surface);
    if (!tex)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(app.rend);
        SDL_DestroyWindow(app.win);
        SDL_Quit();
        return 1;
    }

    // struct to hold the position and size of the sprite
    SDL_Rect dest;

    // get and scale the dimensions of texture
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
    dest.w /= 4;
    dest.h /= 4;

    // start sprite in center of screen
    float x_pos = (WINDOW_WIDTH - dest.w) / 2;
    float y_pos = (WINDOW_HEIGHT - dest.h) / 2;
    float x_vel = 0;
    float y_vel = 0;

    // set to 1 when window close button is pressed
    int close_requested = 0;
    
    // animation loop
    while (!close_requested)
    {
        // process events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                close_requested = 1;
            }
        }

        // get cursor position relative to window
        int mouse_x, mouse_y;
        int buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

        // determine velocity toward mouse
        int target_x = mouse_x - dest.w / 2;
        int target_y = mouse_y - dest.h / 2;
        float delta_x = target_x - x_pos;
        float delta_y = target_y - y_pos;
        float distance = sqrt(delta_x * delta_x + delta_y * delta_y);
        
        // prevent jitter
        if (distance < 5)
        {
            x_vel = y_vel = 0;
        }
        else
        {
            x_vel = delta_x * SPEED / distance;
            y_vel = delta_y * SPEED / distance;
        }

        // reverse velocity if mouse button 1 pressed
        if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            x_vel = -x_vel;
            y_vel = -y_vel;
        }
        
        // update positions
        x_pos += x_vel / 60;
        y_pos += y_vel / 60;

        // collision detection with bounds
        if (x_pos <= 0) x_pos = 0;
        if (y_pos <= 0) y_pos = 0;
        if (x_pos >= WINDOW_WIDTH - dest.w) x_pos = WINDOW_WIDTH - dest.w;
        if (y_pos >= WINDOW_HEIGHT - dest.h) y_pos = WINDOW_HEIGHT - dest.h;

        // set the positions in the struct
        dest.y = (int) y_pos;
        dest.x = (int) x_pos;
        
        // clear the window
        SDL_RenderClear(app.rend);

        // draw the image to the window
        SDL_RenderCopy(app.rend, tex, NULL, &dest);
        SDL_RenderPresent(app.rend);

        // wait 1/60th of a second
        SDL_Delay(1000/60);
    }
    
    // clean up resources before exiting
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(app.rend);
    SDL_DestroyWindow(app.win);
    SDL_Quit();
}
