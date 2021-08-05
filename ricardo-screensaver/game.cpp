#include "game.hpp"
#include "TextureManager.hpp"
#include "gameObject.hpp"

gameObject* player;
//gameObject* player2;

SDL_Renderer* Game::renderer = nullptr;

Game::Game() {

}
Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	screenWidth = 800;
	screenHeight = 600;
	int flags = 0;

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	else {
		flags = SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL initialized." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (window) {
			std::cout << "window created." << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "renderer created." << std::endl;
			
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	player = new gameObject("assets/ricardo.png", 0, 0);
	//player2 = new gameObject("assets/ricardo.png", renderer, 75, 75);
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
		break;
	default:

	break;

	}
}

void Game::update() {
	SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);
	player->initGameObject(screenWidth, screenHeight);
	player->update();
	//player2->update();
}

void Game::render() {
	SDL_RenderClear(renderer);
	//render stuff here
	player->render();
	//player2->render();

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "quit game." << std::endl;
}
