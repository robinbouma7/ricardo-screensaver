#include "TextureManager.hpp"

SDL_Texture* TextureManager::loadTexture(const char* texture) {

	SDL_Surface* tempsurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempsurface);
	SDL_FreeSurface(tempsurface);
	return tex;
}