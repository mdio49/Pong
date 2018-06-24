#pragma once

#include "Ball.h"
#include "Paddle.h"

#define WORLD_WIDTH 1280
#define WORLD_HEIGHT 720
#define WORLD_TOP 20
#define WORLD_BOTTOM WORLD_HEIGHT - WORLD_TOP

#define PADDLE_STARTX 10
#define PADDLE_STARTY (WORLD_HEIGHT - PADDLE_HEIGHT) / 2

#define BALL_STARTX (WORLD_WIDTH - BALL_SIZE) / 2
#define BALL_STARTY (WORLD_HEIGHT - BALL_SIZE) / 2

class World {
public:
	World();

	// Updates the world.
	void update(double dt);

	// Draws the world to the specified render target.
	void draw(SDL_Renderer *rt);

private:
	void updateInput(double dt, const Uint8 *keystate);

	Ball ball;
	Paddle player1;
	Paddle player2;
};
