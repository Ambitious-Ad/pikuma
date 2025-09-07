#pragma once
#include <SDL3/SDL.h>
#include "glm/glm.hpp"

class Game
{
public:
	Game();
	~Game();

	void Setup();
	void Initialize();
	void Run();
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event event;

	Uint32 windowWidth = 320;
	Uint32 windowHeight = 240;
	bool isRunning = false;

	const SDL_DisplayMode* mode = nullptr;
	SDL_DisplayID displayID;

	Uint32 frameWidth = 32;
	Uint32 frameHeight = 32;
	Uint32 frameX = 1 * frameWidth;
	Uint32 frameY = 2 * frameHeight;

	Uint32 millisecsPreviousFrame = 0;

	const Uint32 FPS = 60 ;
	const Uint32 millisecsPerFrame = 1000 / FPS;
	Uint32 frameStart = SDL_GetTicks();

	glm::vec2 playerPosition{ 0.0f,0.0f };
	glm::vec2 playerVelocity{ 0.0f, 0.0f };

};
