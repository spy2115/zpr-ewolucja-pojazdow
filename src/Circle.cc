/*
Jakub Ciarcinski
A struct that represents a circle-type object and holds a pointer to its body for physics.
*/

#include "../include/Circle.h"

Circle createCircle( float x, float y, float radius, float density, float friction, sf::Color color ){
    // Create dynamic body with box shape.
	b2BodyDef body_def;
	body_def.type = b2_dynamicBody;

    // Initial position.
	body_def.position.Set( x / SCALE, y / SCALE );
    b2Body *circle_body = world.CreateBody( &body_def );
	b2CircleShape circle_shape;

    // Set radius for the circle.
    circle_shape.m_radius = radius / SCALE;
    b2FixtureDef circle_fixture_def;
    circle_fixture_def.shape = &circle_shape;
    circle_fixture_def.density = density;
    circle_fixture_def.friction = friction;
    circle_fixture_def.filter.groupIndex = -1;
    circle_body->CreateFixture( &circle_fixture_def );
    
    return Circle{ radius, color, circle_body };
}