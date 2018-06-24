#pragma once

#include <SDL.h>

#include "World.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define TIME_STEP 1.0 / 60.0

// Used to store logic about Pong.
class Pong {
public:
	bool run();

private:
	bool init();
	bool load();
	void loop();
	bool tick(double dt, SDL_Event *e);
	void draw();
	void close();

	SDL_Window *mainWindow;
	SDL_Surface *mainSurface;
	SDL_Renderer *mainRT;

	World world;
};
