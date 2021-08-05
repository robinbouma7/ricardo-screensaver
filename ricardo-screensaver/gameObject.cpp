#include "gameObject.hpp"
#include "textureManager.hpp"
int xborder;
int yborder;
bool up = false;
bool left = false;

gameObject::gameObject(const char* texturesheet, int x, int y) {
	
	objTexture = TextureManager::loadTexture(texturesheet);
	xpos = x;
	ypos = y;
}
void gameObject::initGameObject(int width, int height) {
	xborder = width - 50;
	yborder = height - 50;
	
}
void gameObject::update() {

	if (xpos >= xborder) {
		left = true;
	}
	else if (xpos == 0) {
		left = false;
	}
	else {

	}


	if (ypos >= yborder) {
		up = true;
	}
	else if (ypos == 0) {
		up = false;
	}
	else {

	}


	if (up) {
		ypos--;
	}
	else {
		ypos++;
	}


	if (left) {
		xpos--;
	}
	else {
		xpos++;
	}


	srcRect.h = 25;
	srcRect.w = 25;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}

void gameObject::render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}