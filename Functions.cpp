#include "Functions.h"

#define DIGIT_LENX 3
#define DIGIT_LENY 5
#define DIGIT_SIZE 15
#define DIGITS 10

namespace {
	const char zero[DIGIT_SIZE] = {
		1, 1, 1,
		1, 0, 1,
		1, 0, 1,
		1, 0, 1,
		1, 1, 1
	};

	const char one[DIGIT_SIZE] = {
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
		0, 0, 1
	};

	const char two[DIGIT_SIZE] = {
		1, 1, 1,
		0, 0, 1,
		1, 1, 1,
		1, 0, 0,
		1, 1, 1
	};

	const char three[DIGIT_SIZE] = {
		1, 1, 1,
		0, 0, 1,
		1, 1, 1,
		0, 0, 1,
		1, 1, 1
	};

	const char four[DIGIT_SIZE] = {
		1, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 0, 1,
		0, 0, 1
	};

	const char five[DIGIT_SIZE] = {
		1, 1, 1,
		1, 0, 0,
		1, 1, 1,
		0, 0, 1,
		1, 1, 1
	};

	const char six[DIGIT_SIZE] = {
		1, 1, 1,
		1, 0, 0,
		1, 1, 1,
		1, 0, 1,
		1, 1, 1
	};

	const char seven[DIGIT_SIZE] = {
		1, 1, 1,
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
		0, 0, 1
	};

	const char eight[DIGIT_SIZE] = {
		1, 1, 1,
		1, 0, 1,
		1, 1, 1,
		1, 0, 1,
		1, 1, 1
	};

	const char nine[DIGIT_SIZE] = {
		1, 1, 1,
		1, 0, 1,
		1, 1, 1,
		0, 0, 1,
		0, 0, 1
	};

	const char *digits[DIGITS] = { zero, one, two, three, four, five, six, seven, eight, nine };
}

SDL_Rect rect(int x, int y, int w, int h) {
	return{ x, y, w, h };
}

bool rectIntersect(SDL_Rect rect1, SDL_Rect rect2) {
	if (rect1.x > rect2.x + rect2.w || rect2.x > rect1.x + rect1.w) {
		return false;
	}

	if (rect1.y > rect2.y + rect2.h || rect2.y > rect1.y + rect1.h) {
		return false;
	}

	return true;
}

double rectCenterY(SDL_Rect rect) {
	return rect.y + (rect.h / 2.0);
}

double toRadians(double degrees) {
	return degrees * M_PI / 180;
}

void drawNumber(SDL_Renderer *rt, int number, int x, int y, int scale) {
	// Draw the number's last digit.
	const char *digit = digits[number % 10];
	for (int i = 0; i < DIGIT_LENX; i++) {
		for (int j = 0; j < DIGIT_LENY; j++) {
			if (digit[(j * DIGIT_LENX) + (DIGIT_LENX - i - 1)] == 1) {
				SDL_RenderFillRect(rt, &rect(x - ((i + 1) * scale), y + (j * scale), scale, scale));
			}
		}
	}

	// If the number is larger than 10, then draw the number excluding the last digit to the
	// left of where the last digit was drawn (which recursively draws the entire number).
	if (number >= 10) {
		drawNumber(rt, number / 10, x - scale * (DIGIT_LENX + 1), y, scale);
	}
}

int countDigits(int number) {
	if (number > -10 && number < 10) {
		return 1;
	}

	return 1 + countDigits(number / 10);
}
