#define _CRT_SECURE_NO_WARNINGS

#include "game.hpp"
#include "TextureManager.hpp"
#include "gameObject.hpp"
#include "discord_rpc.h"
#include <time.h>
#include <stdio.h>

gameObject* player;
//gameObject* player2;

SDL_Renderer* Game::renderer = nullptr;
static int64_t StartTime;
//static const char* APPLICATION_ID = "876454630211592252";

Game::Game() {

}
Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	StartTime = time(0);
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

//discord presence
static void handleDiscordReady(const DiscordUser* connectedUser) {
	printf("\nDiscord: connected to user %s#%s - %s\n",
		connectedUser->username,
		connectedUser->discriminator,
		connectedUser->userId);
}

static void handleDiscordDisconnected(int errcode, const char* message) {
	printf("\nDiscord: disconnected (%d: %s)\n", errcode, message);
}

static void handleDiscordError(int errcode, const char* message) {
	printf("\nDiscord: error (%d: %s)\n", errcode, message);
}


void Game::InitDiscord() {
	DiscordEventHandlers handlers;
	memset(&handlers, 1, sizeof(handlers));
	handlers.ready = handleDiscordReady;
	handlers.errored = handleDiscordError;
	handlers.disconnected = handleDiscordDisconnected;

	// Discord_Initialize(const char* applicationId, DiscordEventHandlers* handlers, int autoRegister, const char* optionalSteamId)
	Discord_Initialize("876454630211592252", &handlers, 1, NULL);
}
void Game::UpdatePresence() {
	char hits[256];
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	sprintf(hits, "corner hits: %i", player->cornerhits);
	discordPresence.state = hits;
	discordPresence.details = "ricardo is vibin";
	discordPresence.startTimestamp = StartTime;
	//discordPresence.endTimestamp = time(0) + 5 * 60;
	discordPresence.largeImageKey = "ricardo-512x512";
	discordPresence.largeImageText = "he is chad";
	discordPresence.smallImageText = "very big chad!";
	discordPresence.partyId = "";
	discordPresence.partySize = 0;
	discordPresence.partyMax = 0;
	discordPresence.joinSecret = "";
	Discord_UpdatePresence(&discordPresence);
}

