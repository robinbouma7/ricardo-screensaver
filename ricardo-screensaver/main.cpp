//#include "SDL.h"
#include "game.hpp"
#include "gameobject.hpp"
#include "discord_rpc.h"

Game* game = nullptr;
int frame = 0;
int main(int argc, char* argv[]) {
	
	const int fps = 60;
	const int frameDelay = 1000 / fps;
	
	Uint32 framestart;
	int frametime;


	


	game = new Game();

	game->init("ricardo screensaver", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	game->InitDiscord();
	while (game->running()) {
		frame++;
		framestart = SDL_GetTicks();

		game->handleEvents();
		
		game->update();
		game->render();
		//std::cout << "frame: " << frame << std::endl;

		if (frame == 59) {
			frame = 0;
			game->UpdatePresence();
			//std::cout << "presence updated\n";
		}
		Discord_RunCallbacks();

		frametime = SDL_GetTicks() - framestart;

		if (frameDelay > frametime) {
			SDL_Delay(frameDelay - frametime);
		}

	}
	std::cout << std::endl << SDL_GetError() << std::endl;
	Discord_RunCallbacks();
	SDL_Delay(3000);
	Discord_Shutdown();
	game->clean();

	return 0;
}





