#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

bool Renderer::init()
{

	bool success = true;

	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("Window could not be created, SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Create window and renderer
		if (!SDL_CreateWindowAndRenderer("Hi, mom!", screenWidth, screenHeight, 0, &window, &renderer))
		{
			SDL_Log("renderer could not be created, SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		}
	}
	return success;
}

bool Renderer::loadMedia()
{
	bool success = true;

	texture = loadTexture("image.jpg");
	if (texture == nullptr)
	{
		SDL_Log("Failed to load texture image.\n");
		success = false;
	}
	return success;
}

SDL_Texture* Renderer::loadTexture(std::string path)
{
	SDL_Texture* newTexture = nullptr;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		SDL_Log("Unable to load image %s. SDL_Image Error: %s\n", path.c_str(), SDL_GetError());
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == nullptr)
		{
			SDL_Log("Unable to load image %s. SDL_Image Error: %s\n", path.c_str(), SDL_GetError());
		}

		SDL_DestroySurface(loadedSurface);
	}
	return newTexture;
}

void Renderer::close()
{
	//Free loaded image
	SDL_DestroyTexture(texture);

	//Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = nullptr;
	renderer = nullptr;
	SDL_Quit();
}


void Renderer::run()
{
	if (!init())
	{
		SDL_Log("Failed to initialize.\n");
	}
	else
	{
		if (!loadMedia())
		{
			SDL_Log("Failed to load media.\n");
		}
		else
		{
			bool quit = false;

			SDL_Event e;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_EVENT_QUIT)
					{
						quit = true;
					}
				}

				//Clear the screen
				SDL_RenderClear(renderer);

				//Render texture to the screen
				SDL_RenderTexture(renderer, texture, nullptr, nullptr);

				//Update the screen
				SDL_RenderPresent(renderer);
			}
		}
	}
}
