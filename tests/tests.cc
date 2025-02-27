#define BOOST_TEST_MODULE SFML_Box2D_Example
#include <boost/test/unit_test.hpp>
#include "../include/Car.h"
#include "../include/Button.h"
#include "../include/GA.h"
#include "../include/FileOperations.h"


BOOST_AUTO_TEST_CASE( test_box_create ){
    auto &&box = createBox( 10.0f, 15.0f, 24.0f, 30.0f, 1.f, 0.3f, sf::Color::Black );
    BOOST_CHECK_EQUAL( box.width, 24.0f );
    BOOST_CHECK_EQUAL( box.height, 30.0f );
    BOOST_CHECK( box.color == sf::Color::Black );
    BOOST_CHECK_EQUAL( box.body->GetPosition().x * SCALE, 10.0f );
    BOOST_CHECK_EQUAL( box.body->GetPosition().y * SCALE, 15.0f );
}


BOOST_AUTO_TEST_CASE( test_triangle_create ){
    b2BodyDef body_def;
    body_def.type = b2_dynamicBody;
    body_def.position.Set( 0, 0 );
    b2Body* body = world.CreateBody( &body_def );

    auto &&triangle = createTriangle( body, 5.0f, 8.0f, -3.0f, 6.0f, 9.0f, -4.0f, 1.0f, 0.3f, sf::Color::Blue );
    BOOST_CHECK_EQUAL( triangle.x0, 5.0f );
    BOOST_CHECK_EQUAL( triangle.x1, 8.0f );
    BOOST_CHECK_EQUAL( triangle.x2, -3.0f );
    BOOST_CHECK_EQUAL( triangle.y0, 6.0f );
    BOOST_CHECK_EQUAL( triangle.y1, 9.0f );
    BOOST_CHECK_EQUAL( triangle.y2, -4.0f );
    BOOST_CHECK( triangle.color == sf::Color::Blue );

    const b2PolygonShape* shape = dynamic_cast<const b2PolygonShape*>( body->GetFixtureList()->GetShape() );
    b2Vec2 vertex = body->GetWorldPoint( shape->m_vertices[0] );
    BOOST_CHECK_EQUAL( vertex.x * SCALE, 8.0f );
    BOOST_CHECK_EQUAL( vertex.y * SCALE, 9.0f );

    vertex = body->GetWorldPoint( shape->m_vertices[1] );
    BOOST_CHECK_EQUAL( vertex.x * SCALE, 5.0f );
    BOOST_CHECK_EQUAL( vertex.y * SCALE, 6.0f );

    vertex = body->GetWorldPoint( shape->m_vertices[2] );
    BOOST_CHECK_EQUAL( vertex.x * SCALE, -3.0f );
    BOOST_CHECK_EQUAL( vertex.y * SCALE, -4.0f );
}


BOOST_AUTO_TEST_CASE( test_circle_create ){
    auto &&circle = createCircle( 10.0f, 15.0f, 30.0f, 1.f, 0.3f, sf::Color::Red );
    BOOST_CHECK_EQUAL( circle.radius, 30.0f );
    BOOST_CHECK( circle.color == sf::Color::Red );
    BOOST_CHECK_EQUAL( circle.body->GetPosition().x * SCALE, 10.0f );
    BOOST_CHECK_EQUAL( circle.body->GetPosition().y * SCALE, 15.0f );
}

BOOST_AUTO_TEST_CASE( test_create_ground ){
    std::vector<Box> boxes;
    createGround( boxes, 5.0f, -2.0f, 20.0f, 3.0f, 10, sf::Color::Green );
    BOOST_CHECK_EQUAL( boxes.size(), 10 );
    BOOST_CHECK_EQUAL( boxes[9].height, 3.0f );
    BOOST_CHECK_EQUAL( boxes[9].width, 20.0f );
    BOOST_CHECK( boxes[9].color == sf::Color::Green );
    BOOST_CHECK_EQUAL( boxes[0].body->GetAngle(), 0 );
    BOOST_CHECK_EQUAL( boxes[0].body->GetPosition().x * SCALE, 5 );
    BOOST_CHECK_EQUAL( boxes[0].body->GetPosition().y * SCALE, -2 );
}

BOOST_AUTO_TEST_CASE( test_random_float_generator ){
    float randomized = randomFloatGenerator(0.0f, 1.0f);
    BOOST_CHECK_GE( randomized, 0.0f );
    BOOST_CHECK_LE( randomized, 1.0f );
}

BOOST_AUTO_TEST_CASE( test_button_is_clicked ){
    sf::Font font;
    sf::Vector2i mouse_pos;
    mouse_pos.x = 0;
    mouse_pos.y = 0;
	Button button( 100, 200, 50, 20, "Example Label", font );
    BOOST_CHECK( !button.isClicked( mouse_pos ) );
    mouse_pos.x = 101;
    mouse_pos.y = 201;
    BOOST_CHECK( button.isClicked( mouse_pos ) );
}

BOOST_AUTO_TEST_CASE( test_car_data_create ){
    b2Vec2 p0 = { 80.0f, 0.0f };
	b2Vec2 p1 = { 30.0f, -30.0f };
	b2Vec2 p2 = { 0.0f, -20.0f };
	b2Vec2 p3 = { -40.0f, -30.0f };
	b2Vec2 p4 = { -90.0f, 0.0f };
	b2Vec2 p5 = { -80.0f, 80.0f };
	b2Vec2 p6 = { 0.0f, 50.0f };
	b2Vec2 p7 = { 50.0f, 60.0f };
	b2Vec2 pos = { -10.0f, 600.0f };

	CarData car1_data;
	car1_data.points = { p0, p1, p2, p3, p4, p5, p6, p7 };
	car1_data.pos = pos;
	car1_data.car_density = 1.0f;
	car1_data.car_friction = 0.3f;
	car1_data.wheels_indexes = { 0, 4 };
	car1_data.wheels_radiuses = { 40.0f, 40.0f };
	car1_data.wheels_density = 10.0f;
	car1_data.wheels_friction = 2.0f;
	car1_data.max_speed = -20.0f;
	car1_data.motor_power = 500.0f;
	car1_data.car_color = sf::Color::White;
	car1_data.wheels_color = sf::Color::Blue;

	Car &&car1 = createCar( car1_data );

    BOOST_CHECK_EQUAL( car1.data.points.size(), car1_data.points.size() );
    BOOST_CHECK_EQUAL( car1.data.pos.x, car1_data.pos.x );
    BOOST_CHECK_EQUAL( car1.data.pos.y, car1_data.pos.y );
    BOOST_CHECK_EQUAL( car1.data.car_density, car1_data.car_density );
    BOOST_CHECK_EQUAL( car1.data.car_friction, car1_data.car_friction );
    BOOST_CHECK( car1.data.wheels_indexes == car1_data.wheels_indexes );
    BOOST_CHECK( car1.data.wheels_radiuses == car1_data.wheels_radiuses );
    BOOST_CHECK_EQUAL( car1.data.wheels_density, car1_data.wheels_density );
    BOOST_CHECK_EQUAL( car1.data.wheels_friction, car1_data.wheels_friction );
    BOOST_CHECK_EQUAL( car1.data.max_speed, car1_data.max_speed );
    BOOST_CHECK_EQUAL( car1.data.motor_power, car1_data.motor_power );
    BOOST_CHECK( car1.data.car_color == car1_data.car_color );
    BOOST_CHECK( car1.data.wheels_color == car1_data.wheels_color );
}

BOOST_AUTO_TEST_CASE( test_car_create ){
    b2Vec2 p0 = { 80.0f, 0.0f };
	b2Vec2 p1 = { 30.0f, -30.0f };
	b2Vec2 p2 = { 0.0f, -20.0f };
	b2Vec2 p3 = { -40.0f, -30.0f };
	b2Vec2 p4 = { -90.0f, 0.0f };
	b2Vec2 p5 = { -80.0f, 80.0f };
	b2Vec2 p6 = { 0.0f, 50.0f };
	b2Vec2 p7 = { 50.0f, 60.0f };
	b2Vec2 pos = { -10.0f, 600.0f };

	CarData car1_data;
	car1_data.points = { p0, p1, p2, p3, p4, p5, p6, p7 };
	car1_data.pos = pos;
	car1_data.car_density = 1.0f;
	car1_data.car_friction = 0.3f;
	car1_data.wheels_indexes = { 0, 4 };
	car1_data.wheels_radiuses = { 40.0f, 40.0f };
	car1_data.wheels_density = 10.0f;
	car1_data.wheels_friction = 2.0f;
	car1_data.max_speed = -20.0f;
	car1_data.motor_power = 500.0f;
	car1_data.car_color = sf::Color::White;
	car1_data.wheels_color = sf::Color::Blue;

	Car &&car1 = createCar( car1_data );

    BOOST_CHECK_EQUAL( car1.wheels.size(), 2 );
    BOOST_CHECK_EQUAL( car1.wheels[0].radius, car1_data.wheels_radiuses[0] );
    BOOST_CHECK( car1.wheels[0].color == car1_data.wheels_color );
    BOOST_CHECK_EQUAL( car1.x_start.size(), car1_data.points.size() );
    BOOST_CHECK_EQUAL( car1.x_start[0], car1_data.points[0].x+car1_data.pos.x );
    BOOST_CHECK_EQUAL( car1.y_start.size(), car1_data.points.size() );
    BOOST_CHECK_EQUAL( car1.y_start[0], car1_data.points[0].y+car1_data.pos.y );
    BOOST_CHECK_EQUAL( car1.previous_position, 0 );
    BOOST_CHECK_EQUAL( car1.counter, 0 );
}

BOOST_AUTO_TEST_CASE( test_car_is_stuck ){
    b2Vec2 p0 = { 80.0f, 0.0f };
	b2Vec2 p1 = { 30.0f, -30.0f };
	b2Vec2 p2 = { 0.0f, -20.0f };
	b2Vec2 p3 = { -40.0f, -30.0f };
	b2Vec2 p4 = { -90.0f, 0.0f };
	b2Vec2 p5 = { -80.0f, 80.0f };
	b2Vec2 p6 = { 0.0f, 50.0f };
	b2Vec2 p7 = { 50.0f, 60.0f };
	b2Vec2 pos = { -10.0f, 600.0f };

	CarData car1_data;
	car1_data.points = { p0, p1, p2, p3, p4, p5, p6, p7 };
	car1_data.pos = pos;
	car1_data.car_density = 1.0f;
	car1_data.car_friction = 0.3f;
	car1_data.wheels_indexes = { 0, 4 };
	car1_data.wheels_radiuses = { 40.0f, 40.0f };
	car1_data.wheels_density = 10.0f;
	car1_data.wheels_friction = 2.0f;
	car1_data.max_speed = -20.0f;
	car1_data.motor_power = 500.0f;
	car1_data.car_color = sf::Color::White;
	car1_data.wheels_color = sf::Color::Blue;

	Car &&car1 = createCar( car1_data );

    BOOST_CHECK( !car1.isStuck() );
}

BOOST_AUTO_TEST_CASE( test_car_dump_data ){
    b2Vec2 p0 = { 80.0f, 0.0f };
	b2Vec2 p1 = { 30.0f, -30.0f };
	b2Vec2 p2 = { 0.0f, -20.0f };
	b2Vec2 p3 = { -40.0f, -30.0f };
	b2Vec2 p4 = { -90.0f, 0.0f };
	b2Vec2 p5 = { -80.0f, 80.0f };
	b2Vec2 p6 = { 0.0f, 50.0f };
	b2Vec2 p7 = { 50.0f, 60.0f };
	b2Vec2 pos = { -10.0f, 600.0f };

	CarData car1_data;
	car1_data.points = { p0, p1, p2, p3, p4, p5, p6, p7 };
	car1_data.pos = pos;
	car1_data.car_density = 1.0f;
	car1_data.car_friction = 0.3f;
	car1_data.wheels_indexes = { 0, 4 };
	car1_data.wheels_radiuses = { 40.0f, 40.0f };
	car1_data.wheels_density = 10.0f;
	car1_data.wheels_friction = 2.0f;
	car1_data.max_speed = -20.0f;
	car1_data.motor_power = 500.0f;
	car1_data.car_color = sf::Color::White;
	car1_data.wheels_color = sf::Color::Blue;

	Car &&car1 = createCar( car1_data );

    std::pair<CarData, float> dumped =  car1.dumpData();

    BOOST_CHECK_EQUAL( dumped.first.points.size(), car1_data.points.size() );
    BOOST_CHECK_EQUAL( dumped.first.pos.x, car1_data.pos.x );
    BOOST_CHECK_EQUAL( dumped.first.pos.y, car1_data.pos.y );
    BOOST_CHECK_EQUAL( dumped.first.car_density, car1_data.car_density );
    BOOST_CHECK_EQUAL( dumped.first.car_friction, car1_data.car_friction );
    BOOST_CHECK( dumped.first.wheels_indexes == car1_data.wheels_indexes );
    BOOST_CHECK( dumped.first.wheels_radiuses == car1_data.wheels_radiuses );
    BOOST_CHECK_EQUAL( dumped.first.wheels_density, car1_data.wheels_density );
    BOOST_CHECK_EQUAL( dumped.first.wheels_friction, car1_data.wheels_friction );
    BOOST_CHECK_EQUAL( dumped.first.max_speed, car1_data.max_speed );
    BOOST_CHECK_EQUAL( dumped.first.motor_power, car1_data.motor_power );
    BOOST_CHECK( dumped.first.car_color == car1_data.car_color );
    BOOST_CHECK( dumped.first.wheels_color == car1_data.wheels_color );
}

BOOST_AUTO_TEST_CASE( test_car_create_random ){
	Car &&car1 = createRandomCar( 1.0f, 10.0f, 0.0f, 0.0f, 1.0f, 0.3f, sf::Color::White, 1.0f, 5.0f, 10.0f, 2.0f, -20.0f, 500.0f, sf::Color::Blue );

    BOOST_CHECK_LE( car1.x_start[7], 10.0f );
    BOOST_CHECK_GE( car1.x_start[7], 1.0f );
    BOOST_CHECK_LE( car1.y_start[7], 10.0f );
    BOOST_CHECK_GE( car1.y_start[7], 1.0f );
    BOOST_CHECK_EQUAL( car1.x_start[2], 0.0f );
    BOOST_CHECK_EQUAL( car1.x_start[6], 0.0f );
    BOOST_CHECK_EQUAL( car1.y_start[0], 0.0f );
    BOOST_CHECK_EQUAL( car1.y_start[4], 0.0f );
    BOOST_CHECK_EQUAL( car1.wheels.size(), 2 );
    BOOST_CHECK_GE( car1.wheels[0].radius, 1.0f );
    BOOST_CHECK_LE( car1.wheels[0].radius, 5.0f );
    BOOST_CHECK_EQUAL( car1.wheels.size(), 2 );
    BOOST_CHECK( car1.wheels[0].color == sf::Color::Blue );
    BOOST_CHECK( car1.data.car_color == sf::Color::White );
    BOOST_CHECK_EQUAL( car1.data.car_density, 1.0f );
    BOOST_CHECK_EQUAL( car1.data.car_friction, 0.3f );
    BOOST_CHECK_EQUAL( car1.data.wheels_density, 10.0f );
    BOOST_CHECK_EQUAL( car1.data.wheels_friction, 2.0f );
}

BOOST_AUTO_TEST_CASE( test_json_save_load ){
    b2Vec2 p0 = { 80.0f, 0.0f };
	b2Vec2 p1 = { 30.0f, -30.0f };
	b2Vec2 p2 = { 0.0f, -20.0f };
	b2Vec2 p3 = { -40.0f, -30.0f };
	b2Vec2 p4 = { -90.0f, 0.0f };
	b2Vec2 p5 = { -80.0f, 80.0f };
	b2Vec2 p6 = { 0.0f, 50.0f };
	b2Vec2 p7 = { 50.0f, 60.0f };
	b2Vec2 pos = { -10.0f, 600.0f };

	CarData car1_data;
	car1_data.points = { p0, p1, p2, p3, p4, p5, p6, p7 };
	car1_data.pos = pos;
	car1_data.car_density = 1.0f;
	car1_data.car_friction = 0.3f;
	car1_data.wheels_indexes = { 0, 4 };
	car1_data.wheels_radiuses = { 40.0f, 40.0f };
	car1_data.wheels_density = 10.0f;
	car1_data.wheels_friction = 2.0f;
	car1_data.max_speed = -20.0f;
	car1_data.motor_power = 500.0f;
	car1_data.car_color = sf::Color::White;
	car1_data.wheels_color = sf::Color::Blue;

    std::vector<CarData> data = { car1_data };

    saveCarDataToJson( data, "./tests/test_data.json" );

    std::vector<CarData> loaded_data;

    loadCarDataFromJson( loaded_data, "./tests/test_data.json" );
    
    BOOST_CHECK_EQUAL( loaded_data.size(), 1 );
    BOOST_CHECK_EQUAL( loaded_data[0].points.size(), 8 );
    BOOST_CHECK_EQUAL( loaded_data[0].pos.x, -10.0f );
    BOOST_CHECK_EQUAL( loaded_data[0].pos.y, 600.0f );
    BOOST_CHECK_EQUAL( loaded_data[0].car_density, 1.0f );
    BOOST_CHECK_EQUAL( loaded_data[0].car_friction, 0.3f );
    BOOST_CHECK( loaded_data[0].wheels_indexes == car1_data.wheels_indexes );
    BOOST_CHECK( loaded_data[0].wheels_radiuses == car1_data.wheels_radiuses );
    BOOST_CHECK_EQUAL( loaded_data[0].wheels_density, 10.0f );
    BOOST_CHECK_EQUAL( loaded_data[0].wheels_friction, 2.0f );
    BOOST_CHECK_EQUAL( loaded_data[0].max_speed, -20.0f );
    BOOST_CHECK_EQUAL( loaded_data[0].motor_power, 500.0f );
}

BOOST_AUTO_TEST_CASE( test_ga_create ){
	GeneticAlgorithm saga( 0.1f, 0.2f, 0.9f, 20, 100.0f );

    BOOST_CHECK_EQUAL( saga.getMutationRate(), 0.1f );
    BOOST_CHECK_EQUAL( saga.getMutationPower(), 0.2f );
    BOOST_CHECK_EQUAL( saga.getCrossoverRate(), 0.9f );
    BOOST_CHECK_EQUAL( saga.getSaGens(), 20 );
    BOOST_CHECK_EQUAL( saga.getSaTemperature(), 100.0f );
    BOOST_CHECK_EQUAL( saga.getGeneration(), 0 );
}

BOOST_AUTO_TEST_CASE( test_ga_set_generation ){
	GeneticAlgorithm saga( 0.1f, 0.2f, 0.9f, 20, 100.0f );
    BOOST_CHECK_EQUAL( saga.getGeneration(), 0 );
    saga.setGeneration( 32 );
    BOOST_CHECK_EQUAL( saga.getGeneration(), 32 );
}

BOOST_AUTO_TEST_CASE( test_ga_setCrossoverRate ){
	GeneticAlgorithm saga( 0.1f, 0.2f, 0.9f, 20, 100.0f );
    BOOST_CHECK_EQUAL( saga.getCrossoverRate(), 0.9f );
    saga.setCrossoverRate( 0.72f );
    BOOST_CHECK_EQUAL( saga.getCrossoverRate(), 0.72f );
}

BOOST_AUTO_TEST_CASE( test_ga_set_mutation_rate ){
	GeneticAlgorithm saga( 0.1f, 0.2f, 0.9f, 20, 100.0f );
    BOOST_CHECK_EQUAL( saga.getMutationRate(), 0.1f );
    saga.setMutationRate( 0.442f );
    BOOST_CHECK_EQUAL( saga.getMutationRate(), 0.442f );
}

BOOST_AUTO_TEST_CASE( test_ga_set_mutation_power ){
	GeneticAlgorithm saga( 0.1f, 0.2f, 0.9f, 20, 100.0f );
    BOOST_CHECK_EQUAL( saga.getMutationPower(), 0.2f );
    saga.setMutationPower( 0.123f );
    BOOST_CHECK_EQUAL( saga.getMutationPower(), 0.123f );
}

BOOST_AUTO_TEST_CASE( test_ga_set_sa_gens ){
	GeneticAlgorithm saga( 0.1f, 0.2f, 0.9f, 20, 100.0f );
    BOOST_CHECK_EQUAL( saga.getSaGens(), 20 );
    saga.setSaGens( 40 );
    BOOST_CHECK_EQUAL( saga.getSaGens(), 40 );
}

BOOST_AUTO_TEST_CASE( test_ga_set_sa_temperature ){
	GeneticAlgorithm saga( 0.1f, 0.2f, 0.9f, 20, 100.0f );
    BOOST_CHECK_EQUAL( saga.getSaTemperature(), 100.0f );
    saga.setSaTemperature( 0.61f );
    BOOST_CHECK_EQUAL( saga.getSaTemperature(), 0.61f );
}

BOOST_AUTO_TEST_CASE( test_ga_perform_crossover_on ){
	GeneticAlgorithm saga( 0.1f, 0.2f, 0.9f, 20, 100.0f );
    saga.setCrossoverRate( 1.0f );
    BOOST_CHECK_EQUAL( saga.performCrossover( 0.0f, 1.0f ), 0.5f );
}

BOOST_AUTO_TEST_CASE( test_ga_perform_crossover_off ){
	GeneticAlgorithm saga( 0.1f, 0.2f, 0.9f, 20, 100.0f );
    saga.setCrossoverRate( 0.0f );
    BOOST_CHECK_EQUAL( saga.performCrossover( 0.0f, 1.0f ), 0.0f );
}

BOOST_AUTO_TEST_CASE( test_ga_keep_in_spec ){
	GeneticAlgorithm saga( 0.1f, 0.2f, 0.9f, 20, 100.0f );
    BOOST_CHECK_EQUAL( saga.keepInSpec( 0.1f ), MIN_AXIS );
    BOOST_CHECK_EQUAL( saga.keepInSpec( -0.1f ), -MIN_AXIS );
    BOOST_CHECK_EQUAL( saga.keepInSpec( 100000.0f ), MAX_AXIS );
    BOOST_CHECK_EQUAL( saga.keepInSpec( -100000.0f ), -MAX_AXIS );
    BOOST_CHECK_EQUAL( saga.keepInSpec( 50.0f ), 50.0f );
    BOOST_CHECK_EQUAL( saga.keepInSpec( -50.0f ), -50.0f );
}