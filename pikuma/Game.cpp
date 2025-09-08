#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "Game.h"
#include "Logger.h"

Game::Game() 
{
	isRunning = false;
	Logger::Log("Game constructor called.");
}

Game::~Game() 
{
	Logger::Log("Game destructor called!");
}

void Game::Setup()
{

}

void Game::Initialize()
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("SDL could not initialize. SDL_Error: %s\n", SDL_GetError());
		return;
	}

	displayID = SDL_GetPrimaryDisplay();
	mode = SDL_GetCurrentDisplayMode(displayID);
	if (!mode)
	{
		SDL_Log("Couldn't get display. SDL_Error %s\n", SDL_GetError());
		return;
	}

	windowWidth = mode->w;
	windowHeight = mode->h;
	SDL_Log("Display mode: %dx%d @ %.2fHz", mode->w, mode->h, mode->refresh_rate);

	window = SDL_CreateWindow("Mystic Woods", windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
	if (window == nullptr)
	{
		SDL_Log("Window could not be created. SDL_Error: %s\n", SDL_GetError());
		return;
	}

	renderer = SDL_CreateRenderer(window, nullptr);
	if (!renderer)
	{
		SDL_Log("Failed to create renderer. SDL_Error: %s", SDL_GetError());
		return;
	}

	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	isRunning = true;

}

void Game::Run()
{
	Setup();
	while (isRunning)
	{
		ProcessInput();
		Update();
		Render();

		uint32_t frameEnd = SDL_GetTicks();
		int frameDuration = frameEnd - frameStart;
		if (frameDuration < millisecsPerFrame)
		{
			SDL_Delay(millisecsPerFrame - frameDuration);
		}
	}
}

void Game::ProcessInput()
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_EVENT_KEY_DOWN)
		{
			if (event.key.key == SDLK_ESCAPE)
			{
				isRunning = false;
			}
		}
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
			isRunning = false;
			break;
		default:
			break;
		}
	}
}

void Game::Update()
{
	int timeToWait = millisecsPerFrame - (SDL_GetTicks() - millisecsPreviousFrame);
	double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0f;

	millisecsPreviousFrame = SDL_GetTicks();
}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 21, 21, 255, 255);
	SDL_RenderClear(renderer);

	SDL_Surface* surface = IMG_Load("./sprites/characters/player.png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_DestroySurface(surface);

	SDL_FRect dstRect = { 32, 32, 32, 32 };
	SDL_FRect srcRect = { playerPosition.x, playerPosition.y, 32, 32 };
	SDL_RenderTexture(renderer, texture, &srcRect, &dstRect);

	SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}