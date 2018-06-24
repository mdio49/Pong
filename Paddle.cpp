#include <iostream>

#include "Functions.h"
#include "Paddle.h"
#include "World.h"

Paddle::Paddle() {
	x = 0;
	y = 0;
	vy = 0;
}

SDL_Rect Paddle::getBounds() {
	return rect(x, y, PADDLE_WIDTH, PADDLE_HEIGHT);
}

void Paddle::move(double dt, Direction dir) {
	if (vy > maxVy) {
		vy = maxVy;
	} else if (vy < -maxVy) {
		vy = -maxVy;
	} else {
		vy += ay * dir * dt;
	}

	moving = true;
}

void Paddle::update(double dt) {
	// Move the paddle.
	y += vy * dt;

	// Decelerate the paddle.
	if (!moving) {
		if (vy > ay * dt) {
			vy -= ay * dt;
		} else if (vy < -ay * dt) {
			vy += ay* dt;
		} else {
			vy = 0;
		}
	}

	moving = false;

	if (y < WORLD_TOP) {
		y = WORLD_TOP;
		vy = 0;
	} else if (y > WORLD_BOTTOM - PADDLE_HEIGHT) {
		y = WORLD_BOTTOM - PADDLE_HEIGHT;
		vy = 0;
	}
}

void Paddle::draw(SDL_Renderer *rt) {
	SDL_SetRenderDrawColor(rt, 255, 255, 255, 255);
	SDL_RenderFillRect(rt, &getBounds());
}
