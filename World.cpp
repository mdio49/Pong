#include <SDL.h>

#include "Functions.h"
#include "Pong.h"
#include "World.h"

World::World() {
	player1.x = PADDLE_STARTX;
	player1.y = PADDLE_STARTY;
	player2.x = WORLD_WIDTH - PADDLE_WIDTH - PADDLE_STARTX;
	player2.y = PADDLE_STARTY;

	ball.x = BALL_STARTX;
	ball.y = BALL_STARTY;
	ball.vx = -ball.v0;
}

void World::update(double dt) {
	// Update input.
	const Uint8 *keystate = SDL_GetKeyboardState(nullptr);
	updateInput(dt, keystate);

	// Update the paddles and the ball.
	player1.update(dt);
	player2.update(dt);
	ball.update(dt);

	// Update collisions.
	if (rectIntersect(ball.getBounds(), player1.getBounds()) && (ball.x >= player1.x + player1.getBounds().w + (ball.vx * dt))) {
		ball.doCollision(dt, player1);
	} else if (rectIntersect(ball.getBounds(), player2.getBounds()) && (ball.x <= player2.x + (ball.vx * dt))) {
		ball.doCollision(dt, player2);
	}

	// Check if the ball lands out of bounds.
	if (ball.x < -BALL_SIZE || ball.x > WORLD_WIDTH) {
		if (ball.x < -BALL_SIZE) {
			ball.vx = ball.v0;
			player2.score++;
		} else if (ball.x > WORLD_WIDTH) {
			ball.vx = -ball.v0;
			player1.score++;
		}

		ball.x = BALL_STARTX;
		ball.y = BALL_STARTY;
		ball.vy = 0;
		ball.spin = 0;
	}
}

void World::updateInput(double dt, const Uint8 *keystate) {
	// Movement for player 1.
	if (!player1.ai) {
		if (keystate[SDL_SCANCODE_W]) {
			player1.move(dt, Paddle::Direction::up);
		}
		if (keystate[SDL_SCANCODE_S]) {
			player1.move(dt, Paddle::Direction::down);
		}
	}
	
	// Movement for player 2.
	if (!player2.ai) {
		if (keystate[SDL_SCANCODE_UP]) {
			player2.move(dt, Paddle::Direction::up);
		}
		if (keystate[SDL_SCANCODE_DOWN]) {
			player2.move(dt, Paddle::Direction::down);
		}
	}
}

void World::draw(SDL_Renderer *rt) {
	// Set the render color to white.
	SDL_SetRenderDrawColor(rt, 255, 255, 255, 255);
	
	// Draw the two bars at the top.
	SDL_RenderFillRect(rt, &rect(0, 2, SCREEN_WIDTH, WORLD_TOP - 2));
	SDL_RenderFillRect(rt, &rect(0, WORLD_BOTTOM, SCREEN_WIDTH, WORLD_TOP - 2));

	// Draw the divider in the middle.
	for (int i = 0; i < WORLD_BOTTOM; i += 25) {
		SDL_RenderFillRect(rt, &rect((WORLD_WIDTH / 2) - 4, WORLD_TOP + i, 8, 20));
	}

	// Draw the scores.
	drawNumber(rt, player1.score, WORLD_WIDTH / 2 - 4 - 16, WORLD_TOP + 16, 16);
	drawNumber(rt, player2.score, WORLD_WIDTH / 2 + 4 + (countDigits(player2.score) * 16 * 4), WORLD_TOP + 16, 16);

	// Draw the paddles and the ball.
	player1.draw(rt);
	player2.draw(rt);
	ball.draw(rt);	
}
