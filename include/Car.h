/*
Jakub Ciarcinski, Eryk Jakubowski
Car: A struct that represents a car object and contains the car's body and a vector of circles which are the car's wheels.
CarData: A struct that contains data to create a Car.
*/

#pragma once
#include "./Globals.h"
#include "./Triangle.h"
#include "./Box.h"
#include "./Circle.h"

struct CarData{
	std::vector<b2Vec2> points;
	b2Vec2 pos;
	float car_density;
	float car_friction;
	std::vector<int> wheels_indexes;
	std::vector<float> wheels_radiuses;
	float wheels_density;
	float wheels_friction;
	float max_speed;
	float motor_power;
	sf::Color car_color;
	sf::Color wheels_color;
};

struct Car{
	CarData data;
	b2Body *body;
	std::vector<Circle> wheels;
	std::vector<float> x_start;
	std::vector<float> y_start;
	float traveled_distance;
	float previous_position = 0;
	int counter = 0;
	bool isStuck();
	b2Vec2 getPosition();	// Returns current position of car's middle point.
	void attachWheels( int w1_idx, int w2_idx, float w1_radius, float w2_radius, float density, float friction, float max_speed, float motor_power, sf::Color color );
	void destroy();
	std::pair<CarData, float> dumpData(); // Returns car's data and traveled distance.
	Car(){}
	Car( CarData car_data, b2Body* body ) : data( car_data ), body( body ){}
};

Car createCar( CarData carData );

Car createRandomCar( float min_axis, float max_axis, float x_pos, float y_pos, float density, float friction, sf::Color color, float min_radius, float max_radius, float wheels_density, float wheels_friction, float max_speed, float motor_power, sf::Color wheels_color );
