/*
Jakub Ciarcinski, Eryk Jakubowski
A struct that represents a box-type object and holds a pointer to its body for physics.
*/

#include "../include/Box.h"

Box createBox( float x, float y, float width, float height, float density, float friction, sf::Color color ){
	// Create dynamic body with box shape.
	b2BodyDef box_body_def;
	box_body_def.type = b2_dynamicBody;

	// Initial position.
	box_body_def.position.Set( x / SCALE, y / SCALE );
	b2Body *box_body = world.CreateBody( &box_body_def );
	b2PolygonShape box_shape;
	
	// Set width and height for the box.
	box_shape.SetAsBox( width / 2 / SCALE, height / 2 / SCALE );
	b2FixtureDef fixture_def;
	fixture_def.shape = &box_shape;
	fixture_def.density = density;
	fixture_def.friction = friction;
	box_body->CreateFixture( &fixture_def );

	// Store created body in the Box object.
	return Box{ width, height, color, box_body };
}

void createGround( std::vector<Box> &boxes, float x, float y, float width, float height, int count, sf::Color color ){
	// Clear boxes before creating new ones
	for ( auto& box : boxes ){
        if ( box.body ){
            world.DestroyBody( box.body );
        }
    }
	boxes.clear();
	// Create non-dynamic body with box shape.
	b2BodyDef ground_body_def;
	// Initial angle.
	float angle = 0;
	// Initial position.
	x = x/SCALE;
	y = y/SCALE;

	for ( int i=0; i<count; i++ ){
		ground_body_def.position.Set( x, y );
		ground_body_def.angle = angle;
		b2Body *ground_body = world.CreateBody( &ground_body_def );
		b2PolygonShape ground_box;

		ground_box.SetAsBox( width / 2 / SCALE, height / 2 / SCALE );
		ground_body->CreateFixture( &ground_box, 0.0f );

		// Increasing angle.
		b2Vec2 vertex = dynamic_cast<b2PolygonShape*>( ground_body->GetFixtureList()->GetShape() )->m_vertices[ 2 ];
		if ( i > 5 && i < count / 4 ){
			angle = randomFloatGenerator( -0.39, 0.39 );
		} else if ( i >= count / 4 && i < count / 2 ){
			angle = randomFloatGenerator( -0.78, 0.78 );
		} else if ( i >= count / 2 && i < count * 7 / 8 ){
			angle = randomFloatGenerator( -1.17, 1.17 );
		} else if ( i >= count * 7 / 8 ){
			angle = randomFloatGenerator( -1.56, 1.56 );
		} 
		
		x = ground_body->GetWorldPoint( vertex ).x + std::cos( angle ) * ( width/2 ) / SCALE + std::sin( angle ) * ( height / 2 ) / SCALE;
		y = ground_body->GetWorldPoint( vertex ).y + std::sin( angle ) * ( width/2 ) / SCALE - std::cos( angle ) * ( height / 2 ) / SCALE;

		boxes.push_back( Box{ width, height, color, ground_body } );
	}
}