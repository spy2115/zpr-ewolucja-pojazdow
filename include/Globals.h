/*
Jakub Ciarcinski
Global variables used in this project.
*/

#pragma once
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

#ifndef GLOBALS_H
#define GLOBALS_H
extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

extern float MIN_RADIUS;
extern float MAX_RADIUS;
extern float MIN_AXIS;
extern float MAX_AXIS;
// Pixels per meter. Box2D uses metric units, so we need to define a conversion.
extern int SCALE;
// SFML uses degrees for angles while Box2D uses radians.
extern float DEG_PER_RAD;

// Seed for random number generator.
extern unsigned int SEED;
extern int SPEED;
 
extern float GRAVITY;

// Box2D world for physics simulation, gravity = 9.81 m/s^2.
extern b2World world;
#endif