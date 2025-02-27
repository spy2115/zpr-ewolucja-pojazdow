/*
Jakub Ciarcinski
A struct that represents a triangle-type object with its vertices.
*/

#include "../include/Triangle.h"

bool arePointsCollinear( float x0, float y0, float x1, float y1 ){
    if ( abs( ( x0/y0 ) - ( x1/y1 ) ) < 0.01 ){return true;}
    return false;
}

Triangle createTriangle( b2Body* body, float x0, float x1, float x2, float y0, float y1, float y2, float density, float friction, sf::Color color ){
    b2PolygonShape dynamic_triangle;
    if ( arePointsCollinear( x0, y0, x1, y1 ) ){
        // Adjust one of the points slightly to make them non-collinear, one coordinate is enough.
        x0 += 10.0f * ( x1/y1 );
    }
    b2Vec2 vertices[3];
    vertices[0].Set( x0 / SCALE, y0 / SCALE );
    vertices[1].Set( x1 / SCALE, y1 / SCALE );
    vertices[2].Set( x2 / SCALE, y2 / SCALE );
    dynamic_triangle.Set( vertices, 3 );
    b2FixtureDef fixture_def;
    fixture_def.shape = &dynamic_triangle;
    fixture_def.density = density;
    fixture_def.friction = friction;
    fixture_def.filter.groupIndex = -1;
    body->CreateFixture( &fixture_def );

	return Triangle{ x0, x1, x2, y0, y1, y2, color };
}
