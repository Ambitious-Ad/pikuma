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
	}
}

void Game::ProcessInput()
{

}

void Game::Update()
{

}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer);


}

void Game::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}