/*
Jakub Ciarcinski, Eryk Jakubowski
Car: A struct that represents a car object and contains the car's body and a vector of circles which are the car's wheels.
CarData: A struct that contains data to create a Car.
*/

#include "../include/Car.h"

void Car::destroy(){
    if ( body ){
        // Destroy the body
        body->GetWorld()->DestroyBody( body );
        body = nullptr;
    }
    for ( auto& wheel : wheels ){
        if ( wheel.body ){
            // Destroy the wheel body
            wheel.body->GetWorld()->DestroyBody( wheel.body );
            wheel.body = nullptr;
        }
    }
}

// Returns current position of car's middle point.
b2Vec2 Car::getPosition(){
    b2Fixture* fixture = this->body->GetFixtureList();

    b2Vec2 vertex0a = dynamic_cast<b2PolygonShape*>( fixture->GetShape() )->m_vertices[0];
    b2Vec2 vertex1a = dynamic_cast<b2PolygonShape*>( fixture->GetShape() )->m_vertices[1];
    b2Vec2 vertex2a = dynamic_cast<b2PolygonShape*>( fixture->GetShape() )->m_vertices[2];

    fixture = fixture->GetNext();
    fixture = fixture->GetNext();

    b2Vec2 vertex0b = dynamic_cast<b2PolygonShape*>( fixture->GetShape() )->m_vertices[0];
    b2Vec2 vertex1b = dynamic_cast<b2PolygonShape*>( fixture->GetShape() )->m_vertices[1];
    b2Vec2 vertex2b = dynamic_cast<b2PolygonShape*>( fixture->GetShape() )->m_vertices[2];

    // Finding a common vertex.
    if ( vertex0a.x == vertex0b.x || vertex0a.x == vertex1b.x || vertex0a.x == vertex2b.x ){
        return this->body->GetWorldPoint( vertex0a );
    } else if ( vertex1a.x == vertex0b.x || vertex1a.x == vertex1b.x || vertex1a.x == vertex2b.x ){
        return this->body->GetWorldPoint( vertex1a );
    } else{
        return this->body->GetWorldPoint( vertex2a );
    }
}

bool Car::isStuck(){
    float current_x = getPosition().x;
    if ( counter >= 600 / SPEED ){
        return true;
    }
    if ( abs( current_x - previous_position ) <= 0.1 || current_x < 0.0 ){
        counter += 1;
        this->previous_position = current_x;
    } else{
        counter = 0;
        this->previous_position = current_x;
    }
    return false;
}

// Returns car's data and traveled distance.
std::pair<CarData, float> Car::dumpData(){
    return{ this->data, this->traveled_distance };
}

Car createCar( CarData car_data ){
    b2BodyDef body_def;
    body_def.type = b2_dynamicBody;
    // Initial position.
    body_def.position.Set( car_data.pos.x / SCALE, car_data.pos.y / SCALE );
    // Creating car's body of triangles.
    b2Body* body = world.CreateBody( &body_def );
    auto &&triangle0 = createTriangle( body, car_data.points[0].x, car_data.points[1].x, 0.0f, car_data.points[0].y, car_data.points[1].y, 0.0f, car_data.car_density, car_data.car_friction, car_data.car_color );
    auto &&triangle1 = createTriangle( body, car_data.points[1].x, car_data.points[2].x, 0.0f, car_data.points[1].y, car_data.points[2].y, 0.0f, car_data.car_density, car_data.car_friction, car_data.car_color );
    auto &&triangle2 = createTriangle( body, car_data.points[2].x, car_data.points[3].x, 0.0f, car_data.points[2].y, car_data.points[3].y, 0.0f, car_data.car_density, car_data.car_friction, car_data.car_color );
    auto &&triangle3 = createTriangle( body, car_data.points[3].x, car_data.points[4].x, 0.0f, car_data.points[3].y, car_data.points[4].y, 0.0f, car_data.car_density, car_data.car_friction, car_data.car_color );
    auto &&triangle4 = createTriangle( body, car_data.points[4].x, car_data.points[5].x, 0.0f, car_data.points[4].y, car_data.points[5].y, 0.0f, car_data.car_density, car_data.car_friction, car_data.car_color );
    auto &&triangle5 = createTriangle( body, car_data.points[5].x, car_data.points[6].x, 0.0f, car_data.points[5].y, car_data.points[6].y, 0.0f, car_data.car_density, car_data.car_friction, car_data.car_color );
    auto &&triangle6 = createTriangle( body, car_data.points[6].x, car_data.points[7].x, 0.0f, car_data.points[6].y, car_data.points[7].y, 0.0f, car_data.car_density, car_data.car_friction, car_data.car_color );
    auto &&triangle7 = createTriangle( body, car_data.points[7].x, car_data.points[0].x, 0.0f, car_data.points[7].y, car_data.points[0].y, 0.0f, car_data.car_density, car_data.car_friction, car_data.car_color );
    Car car{ car_data, body };
    // Calculating starting positions of vertices.
    car.x_start = { car_data.points[0].x+car_data.pos.x, car_data.points[1].x+car_data.pos.x, car_data.points[2].x+car_data.pos.x, car_data.points[3].x+car_data.pos.x, car_data.points[4].x+car_data.pos.x, car_data.points[5].x+car_data.pos.x, car_data.points[6].x+car_data.pos.x, car_data.points[7].x+car_data.pos.x };
    car.y_start = { car_data.points[0].y+car_data.pos.y, car_data.points[1].y+car_data.pos.y, car_data.points[2].y+car_data.pos.y, car_data.points[3].y+car_data.pos.y, car_data.points[4].y+car_data.pos.y, car_data.points[5].y+car_data.pos.y, car_data.points[6].y+car_data.pos.y, car_data.points[7].y+car_data.pos.y };
    car.attachWheels( car_data.wheels_indexes[0], car_data.wheels_indexes[1], car_data.wheels_radiuses[0], car_data.wheels_radiuses[1], car_data.wheels_density, car_data.wheels_friction, car_data.max_speed, car_data.motor_power, car_data.wheels_color );

    return car;
}


Car createRandomCar( float min_axis, float max_axis, float x_pos, float y_pos, float density, float friction, sf::Color color, float min_radius, float max_radius, float wheels_density, float wheels_friction, float max_speed, float motor_power, sf::Color wheels_color ){
    // Generating random vertices.
    b2Vec2 p0 = { randomFloatGenerator( min_axis, max_axis ), 0.0f };
    b2Vec2 p1 = { randomFloatGenerator( min_axis, max_axis ), -randomFloatGenerator( min_axis, max_axis ) };
    b2Vec2 p2 = { 0.0f, -randomFloatGenerator( min_axis, max_axis ) };
    b2Vec2 p3 = { -randomFloatGenerator( min_axis, max_axis ), -randomFloatGenerator( min_axis, max_axis ) };
    b2Vec2 p4 = { -randomFloatGenerator( min_axis, max_axis ), 0.0f };
    b2Vec2 p5 = { -randomFloatGenerator( min_axis, max_axis ), randomFloatGenerator( min_axis, max_axis ) };
    b2Vec2 p6 = { 0.0f, randomFloatGenerator( min_axis, max_axis ) };
    b2Vec2 p7 = { randomFloatGenerator( min_axis, max_axis ), randomFloatGenerator( min_axis, max_axis ) };

    std::vector<b2Vec2> points = { p0, p1, p2, p3, p4, p5, p6, p7 };
    b2Vec2 pos = { x_pos, y_pos };
    std::vector<int> wheels_indexes = { int( randomFloatGenerator( 0, 7.99 ) ), int( randomFloatGenerator( 0, 7.99 ) ) };
    std::vector<float> wheels_radiuses = { randomFloatGenerator( min_radius, max_radius ), randomFloatGenerator( min_radius, max_radius ) };

    CarData car_data = { points, pos, density, friction, wheels_indexes, wheels_radiuses, wheels_density, wheels_friction, max_speed, motor_power, color, wheels_color };
    return createCar( car_data );
}

void Car::attachWheels( int w1_idx, int w2_idx, float w1_radius, float w2_radius, float density, float friction, float max_speed, float motor_power, sf::Color color ){
    // Creating wheels with middle points in a vertex of given index.
    auto &&wheel1 = createCircle( this->x_start[w1_idx], this->y_start[w1_idx], w1_radius, density, friction, color );
	auto &&wheel2 = createCircle( this->x_start[w2_idx], this->y_start[w2_idx], w2_radius, density, friction, color );

    // Connecting wheels to the car's body.
    b2RevoluteJointDef joint_def1;
    joint_def1.Initialize( this->body, wheel1.body, wheel1.body->GetWorldCenter() );

    joint_def1.motorSpeed = max_speed;
    joint_def1.maxMotorTorque = motor_power;
    joint_def1.enableMotor = true;

    joint_def1.lowerAngle = -wheel1.radius;
    joint_def1.upperAngle = wheel1.radius;

    world.CreateJoint( &joint_def1 );

    b2RevoluteJointDef joint_def2;
    joint_def2.Initialize( this->body, wheel2.body, wheel2.body->GetWorldCenter() );

    joint_def2.motorSpeed = max_speed;
    joint_def2.maxMotorTorque = motor_power;
    joint_def2.enableMotor = true;

    joint_def2.lowerAngle = -wheel1.radius;
    joint_def2.upperAngle = wheel1.radius;

    world.CreateJoint( &joint_def2 );
    this->wheels = { wheel1, wheel2 };
}
