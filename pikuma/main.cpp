#include <iostream>
#include <SDL3/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;

	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("Window could not be created, SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		window = SDL_CreateWindow("Hi, mom!", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		if (window == nullptr)
		{
			SDL_Log("Window could not be created, SDL_Error: %s\n", SDL_GetError());
		}
		screenSurface = SDL_GetWindowSurface(window);
		SDL_FillSurfaceRect(screenSurface, nullptr, SDL_MapSurfaceRGB(screenSurface, 0xFF, 0xFF, 0xFF));

		SDL_UpdateWindowSurface(window);
		SDL_Delay(3000);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}