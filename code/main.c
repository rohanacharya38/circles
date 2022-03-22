// inlcudes
#include "threading.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <SDL.h>
#include <stdio.h>
#include <stdint.h>
//
//

// defines
#define SCREEN_WIDTH 1350
#define SCREEN_HEIGHT 700
#define RECT_COUNT 190
#define sWIDTH 6
#define PADDING 1
#define mid_x 675
#define mid_y 350
#define RADIUS 50
// emum for bool
typedef enum
{
    false,
    true
} bool;
// lets use midpoint algorithm to  draw a circle
void draw_circle(SDL_Renderer *renderer, int centre_x, int centre_y, int radius);

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    bool is_running = true;
    SDL_Event event;
    int centre_x = 1, centre_y = 1;

    for (int i = 0; is_running; i++)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                is_running = false;
        }
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            draw_circle(renderer, centre_x, centre_y, 2 * i);

            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            draw_circle(renderer, centre_x, centre_y, 2 * i * 0.8);

            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            draw_circle(renderer, centre_x, centre_y, 2 * i * 0.6);
            SDL_RenderPresent(renderer);
            SDL_Delay(10);
            centre_x+=3;
            centre_y+=3;


            if(centre_x>SCREEN_WIDTH)
            is_running=false;
        }
    }
    return 0;
}

void draw_circle(SDL_Renderer *renderer, int x0, int y0, int radius)
{
    int x = radius - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);
    while (x >= y)
    {
        SDL_RenderDrawPoint(renderer, x0 + x, y0 + y);
        SDL_RenderDrawPoint(renderer, x0 + x, y0 - y);
        SDL_RenderDrawPoint(renderer, x0 - x, y0 + y);
        SDL_RenderDrawPoint(renderer, x0 - x, y0 - y);
        SDL_RenderDrawPoint(renderer, x0 + y, y0 + x);
        SDL_RenderDrawPoint(renderer, x0 + y, y0 - x);
        SDL_RenderDrawPoint(renderer, x0 - y, y0 + x);
        SDL_RenderDrawPoint(renderer, x0 - y, y0 - x);
        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}
