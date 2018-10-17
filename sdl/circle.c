#include <math.h>
#include "SDL.h"

int 
main(int argc, char* argv[])
{

  int width = 640;
  int height = 480;

  float r = 60.0;
  float x = 0.0;
  float y = 0.0;
  float a = 0.0; // two pi full rotation

  if (SDL_Init(SDL_INIT_VIDEO) == 0) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer) == 0) {
      SDL_bool done = SDL_FALSE;

      while (!done) {
        SDL_Event event;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        x = width / 2 + cos(a) * r;
        y = height / 2 + sin(a) * r;
        a += 0.01;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawPoint(renderer, x++, y++);
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
          if (event.type == SDL_QUIT) {
            done = SDL_TRUE;
          }
        }
      }
    }

    if (renderer) {
      SDL_DestroyRenderer(renderer);
    }
    if (window) {
      SDL_DestroyWindow(window);
    }
  }

  SDL_Quit();

  return 0;
}
