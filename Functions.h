#pragma once

#include <SDL.h>
// Gets a rectange with the given dimensions.
SDL_Rect rect(int x, int y, int w, int h);

// Determines if two rectangles are intersecting.
bool rectIntersect(SDL_Rect rect1, SDL_Rect rect2);

// Gets the y-component of the center of the given rectangle.
double rectCenterY(SDL_Rect rect);

// Converts the given angle in degrees to radians.
double toRadians(double degrees);

/* Draws a number to the screen.
x - Rightmost position of number.
y - Topmost position of number.
scale - The size of each digit pixel. */
void drawNumber(SDL_Renderer *rt, int number, int x, int y, int scale);

// Counts the number of digits in the given integer.
int countDigits(int number);
