#pragma once
#include "game.hpp"

class gameObject {

public:
	gameObject(const char* texturesheet, int x, int y);
	~gameObject();
	void initGameObject(int width, int height);

	void update();
	void render();

private:

	int xpos;
	int ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;

};