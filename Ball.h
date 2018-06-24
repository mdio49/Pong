#pragma once

#include <SDL.h>

#include "Paddle.h"

#define BALL_SIZE 16

class Ball {
public:
	Ball();

	SDL_Rect getBounds();

	double getVelocity();
	double getDirection();

	void doCollision(double dt, Paddle paddle);

	void update(double dt);
	void draw(SDL_Renderer *rt);

	double x;
	double y;

	double vx;
	double vy;

	double spin;

	const double v0 = 240;

private:
	const double a = 0.18;
};
