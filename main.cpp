/*
 * @Author: Lukasz
 * @Date:   12-10-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 12-10-2018
 */
// #include "SDL.h"
// #include "SDL/SDL.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// #include "SDL.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

// SDL_Surface *screen;

// void putpixel(int x, int y, int color)
// {
//   unsigned int *ptr        = (unsigned int *)screen->pixels;
//   int           lineoffset = y * (screen->pitch / 4);
//   ptr[lineoffset + x]      = color;
// }

// void render(SDL_Surface *screen)
// {
//   // Lock surface if needed
//   if (SDL_LockSurface(screen) < 0)
//     return;

//   // Ask SDL for the time in milliseconds
//   int tick = SDL_GetTicks();

//   // Declare a couple of variables
//   int i, j, yofs, ofs;

//   // Draw to screen
//   yofs = 0;
//   for (i = 0; i < 480; i++)
//   {
//     for (j = 0, ofs = yofs; j < 640; j++, ofs++)
//     {
//       ((unsigned int *)screen->pixels)[ofs] = i * i + j * j + tick;
//     }
//     yofs += screen->pitch / 4;
//   }

//   putpixel(10, 10, 0xff0000);
//   putpixel(11, 10, 0xff0000);
//   putpixel(10, 11, 0xff0000);
//   putpixel(11, 11, 0xff0000);

//   // Unlock if needed
//   if (SDL_MUSTLOCK(screen))
//     SDL_UnlockSurface(screen);

//   // Tell SDL to update the whole screen
//   // SDL_UpdateRect(screen, 0, 0, 640, 480);
//   // SDL_UpdateTexture(screen, 0, 0, 640, 480);
// }

// Entry point
int main(int argc, char *argv[])
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  auto win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
  if (win == nullptr)
  {
    std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  auto ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (ren == nullptr)
  {
    SDL_DestroyWindow(win);
    std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  auto imagePath   = "./tux.png";
  auto tux_surface = IMG_Load(imagePath);
  if (tux_surface == nullptr)
  {
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, tux_surface);
  SDL_FreeSurface(tux_surface);
  if (tex == nullptr)
  {
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  // A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
  for (int i = 0; i < 3; ++i)
  {
    // First clear the renderer
    SDL_RenderClear(ren);
    // Draw the texture
    SDL_RenderCopy(ren, tex, NULL, NULL);
    // Update the screen
    SDL_RenderPresent(ren);
    // Take a quick break after all that hard work
    SDL_Delay(1000);
  }

  SDL_DestroyTexture(tex);
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();

  return 0;
}
