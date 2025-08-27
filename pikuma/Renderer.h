#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>

class Renderer
{
public:
	Renderer();
	~Renderer();

	void run();
	bool loadMedia();
	bool init();
	SDL_Texture* loadTexture(std::string path);
	void close();

private:
	const int screenWidth = 640;
	const int screenHeight = 480;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;

};

