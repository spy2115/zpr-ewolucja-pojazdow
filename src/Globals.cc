/*
Jakub Ciarcinski
Global variables used in this project.
*/

#include "../include/Globals.h"

float MIN_RADIUS = 15.0;
float MAX_RADIUS = 50.0;
float MIN_AXIS = 20.0;
float MAX_AXIS = 100.0;

int WINDOW_WIDTH = 1720;
int WINDOW_HEIGHT = 900;

int SCALE = 30;
float DEG_PER_RAD = 57.2957795f;
unsigned int SEED = 42;
float GRAVITY = 9.81;
int SPEED = 2;
b2World world( b2Vec2( 0, -GRAVITY ) );