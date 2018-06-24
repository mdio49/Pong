#include "Ball.h"
#include "Functions.h"
#include "World.h"

Ball::Ball() {
	x = 0;
	y = 0;
	vx = 0;
	vy = 0;
	spin = 0;
}

SDL_Rect Ball::getBounds() {
	return rect(x, y, BALL_SIZE, BALL_SIZE);
}

double Ball::getVelocity() {
	return SDL_sqrt((vx * vx) + (vy * vy));
}

double Ball::getDirection() {
	return SDL_atan2(vy, vx);
}

void Ball::doCollision(double dt, Paddle paddle) {
	// Reverse the direction of the ball.
	vx = -vx;
	x += vx * dt;
	spin = -toRadians(paddle.vy / 32.0);

	// Change the direction of the ball based on the position of the paddle.
	double changeDir = (rectCenterY(paddle.getBounds()) - rectCenterY(this->getBounds())) / 25.0;
	double newDir = getDirection() + (vx > 0 ? -changeDir : changeDir);
	double v = getVelocity();
	vx = v * SDL_cos(newDir);
	vy = v * SDL_sin(newDir);
}

void Ball::update(double dt) {
	// Check if the ball touches the edges of the arena.
	if (y < WORLD_TOP || y > WORLD_BOTTOM - BALL_SIZE) {
		vy = -vy;
	}

	// Move the ball.
	x += vx * dt;
	y += vy * dt;

	// Accelerate the ball gradually overtime.
	double dir = getDirection();
	vx += a * SDL_cos(dir) * dt;
	vy += a * SDL_sin(dir) * dt;

	// Apply a spin to the ball.
	dir += spin * dt;
	double v = getVelocity();
	vx = v * SDL_cos(dir);
	vy = v * SDL_sin(dir);
}

void Ball::draw(SDL_Renderer *rt) {
	SDL_SetRenderDrawColor(rt, 255, 255, 255, 255);
	SDL_RenderFillRect(rt, &getBounds());
}
