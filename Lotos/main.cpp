#include <iostream>
#include "SDL.h"

int main(int argc, char* argv[]) {
	std::cout << "Hello, World!" << std::endl;
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* windows = SDL_CreateWindow("Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(windows, -1, 0);
	SDL_SetRenderDrawColor(renderer, 123, 200, 10, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_Delay(3000);
	return 0;
}