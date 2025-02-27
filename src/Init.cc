/*
Eryk Jakubowski
Function that sets up data used in the project.
*/

#include "../include/Init.h"

void init( std::vector<Box> &boxes, std::vector<float> &boxes_x, std::vector<float> &boxes_y, std::vector<Car> &cars, std::vector<CarData> &cars_data, std::vector<std::vector<std::pair<float, float>>> &cars_positions, float &track_start, float &track_end ){
	boxes_x.clear();
	boxes_y.clear();
	for ( auto& car : cars ){
    car.destroy();
	}
	cars.clear();
	cars_data.clear();
	cars_positions.clear();
	createGround( boxes, -300, 400, 150, 10, 150, sf::Color::Green );
	float y_min = 0;
	float y_max = 0;
	float y_scale;
	for ( auto& box : boxes ){
		b2Vec2 vertex = dynamic_cast<b2PolygonShape*>( box.body->GetFixtureList()->GetShape() )->m_vertices[ 3 ];
		b2Vec2 vertex2 = dynamic_cast<b2PolygonShape*>( box.body->GetFixtureList()->GetShape() )->m_vertices[ 2 ];
		boxes_x.push_back( box.body->GetWorldPoint( vertex ).x );
		boxes_x.push_back( box.body->GetWorldPoint( vertex2 ).x );
		boxes_y.push_back( box.body->GetWorldPoint( vertex ).y );
		boxes_y.push_back( box.body->GetWorldPoint( vertex2 ).y );
		if( box.body->GetWorldPoint( vertex ).y > y_max ){ y_max = box.body->GetWorldPoint( vertex ).y;}
		if( box.body->GetWorldPoint( vertex ).y < y_min ){ y_min = box.body->GetWorldPoint( vertex ).y;}
		if( box.body->GetWorldPoint( vertex2 ).y < y_min ){ y_min = box.body->GetWorldPoint( vertex ).y;}
		if( box.body->GetWorldPoint( vertex2 ).y < y_min ){ y_min = box.body->GetWorldPoint( vertex ).y;}
	}
	if ( abs( y_min ) > abs( y_max ) ){
		y_scale = abs( y_min );
	} else{
		y_scale = abs( y_max );
	}
	track_start = boxes_x[0];
	track_end = boxes_x[boxes_x.size() - 1];
	// Scaling.
	for ( auto& x : boxes_x ){
		x = ( ( x - track_start ) * WINDOW_WIDTH / track_end );
	}
	for ( auto& y : boxes_y ){
		y = y * WINDOW_HEIGHT / 4 / y_scale;
	}
	for ( int i=0; i < 20; ++i ){
		Car &&car_random = createRandomCar( MIN_AXIS, MAX_AXIS, 30.0f, 800.0f, 1.0f, 0.3f, sf::Color::White, MIN_RADIUS, MAX_RADIUS, 10.0f, 0.95f, -20.0f, 500.0f, sf::Color( 128, 128, 128 ) );
		cars.push_back( car_random );
		cars_data.push_back( car_random.data );
	}
	std::vector<std::pair<float, float>> blank;
	for ( auto &car_data : cars_data ){
		car_data.car_color = sf::Color::White;
		car_data.wheels_color = sf::Color( 128, 128, 128 );

		cars_positions.push_back( blank );

		car_data.car_color.a = 128;
		car_data.wheels_color.a = 128;
		cars.push_back( createCar( car_data ) );
	}
}