#include <iostream>
#include <SDL.h>

#include "Pong.h"

using namespace std;

// Call this function to run the game. The return value of this function should be passed
// into the return value of the program's main function.
bool Pong::run() {
	if (!init()) {
		return EXIT_FAILURE;
	}

	if (!load()) {
		return EXIT_FAILURE;
	}

	loop();
	close();

	return EXIT_SUCCESS;
}

// Initializes the game and returns a value indicating if it was successful.
bool Pong::init() {
	// Initialize SDL.
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
		return false;
	}

	// Create the main window.
	mainWindow = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
								  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (mainWindow == nullptr) {
		cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
		return false;
	}

	// Gets the main window surface.
	mainSurface = SDL_GetWindowSurface(mainWindow);

	// Create the main render target.
	mainRT = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

	return true;
}

// Loads resources into the game and returns a value indicating if it was successful.
bool Pong::load() {

	// LOAD ANY RESOURCES HERE.

	return true;
}

// Initiates the start of the main game loop.
void Pong::loop() {
	SDL_Event e;
	bool quit = false;
	double ticks = SDL_GetTicks();

	// Enter the main game loop.
	while (!quit) {
		double dt = (SDL_GetTicks() - ticks) / 1000;
		ticks = SDL_GetTicks();
		if (tick(dt, &e)) {
			quit = true;
		}
		draw();
	}
}

// Updates the game for one frame of length 'dt'. Returns true if the game should exit.
bool Pong::tick(double dt, SDL_Event *e) {
	bool quit = false;

	// Handles SDL events.
	while (SDL_PollEvent(e) != 0) {
		switch (e->type) {
			case SDL_QUIT:
				quit = true;
				break;
			// PUT ANY SDL EVENTS HERE.
		}
	}

	// Update the world.
	world.update(dt);

	return quit;
}

// Draws the game's current frame.
void Pong::draw() {
	// Clear the render target black.
	SDL_SetRenderDrawColor(mainRT, 0, 0, 0, 255);
	SDL_RenderClear(mainRT);

	// Draws the world.
	world.draw(mainRT);

	// Present the render target onto the main window.
	SDL_RenderPresent(mainRT);
}

// Closes the game, destroying the window and freeing any resources.
void Pong::close() {
	// Destroy the window.
	SDL_DestroyWindow(mainWindow);
	mainWindow = nullptr;

	SDL_DestroyRenderer(mainRT);

	// Quit SDL.
	SDL_Quit();
}
