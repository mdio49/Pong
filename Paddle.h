#pragma once

#include <SDL.h>

#define PADDLE_WIDTH 25
#define PADDLE_HEIGHT 55

class Paddle {
public:
	enum Direction {
		up = -1,
		down = 1
	};

	Paddle();

	SDL_Rect getBounds();

	void move(double dt, Direction dir);

	void update(double dt);
	void draw(SDL_Renderer *rt);

	double x;
	double y;

	double vy;

	// The score of the player controlling the paddle.
	int score = 0;

	// Indicates if the paddle is being controlled by an AI.
	bool ai = false;

private:
	// Indicates if the paddle is being moved.
	bool moving = false;

	const double maxVy = 420.0;
	const double ay = 1080;
};

