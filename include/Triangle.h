/*
Jakub Ciarcinski
A struct that represents a triangle-type object with its vertices.
*/

#pragma once
#include "./Globals.h"

struct Triangle{
	float x0, x1, x2;
	float y0, y1, y2;
	sf::Color color;
};

bool arePointsCollinear( float x0, float y0, float x1, float y1 );
Triangle createTriangle( b2Body* body, float x0, float x1, float x2, float y0, float y1, float y2, float density, float friction, sf::Color color );