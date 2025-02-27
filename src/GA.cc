/*
Eryk Jakubowski
A class that represents a genetic algorithm with its parameters and performs selection, crossover and mutation on its population each generation.
*/

#include "../include/GA.h"

int GeneticAlgorithm::getGeneration(){
    return generation_;
}

float GeneticAlgorithm::performCrossover( float data1, float data2 ){
    if( randomFloatGenerator( 0.0, 1.0 ) <= crossover_rate_ ){
        return ( ( data1 + data2 ) / 2 );
    } else{
        return data1;
    }
}

float GeneticAlgorithm::keepInSpec( float data ){
    if ( data == 0 ){
        return data;
    }
    if ( abs( data ) > MAX_AXIS ){
        if ( data < 0 ){
            return -MAX_AXIS;
        } else{
            return MAX_AXIS;
        }
    }
    if ( abs( data ) < MIN_AXIS ){
        if ( data < 0 ){
            return -MIN_AXIS;
        } else{
            return MIN_AXIS;
        }
    }
    return data;
};

CarData GeneticAlgorithm::crossover( std::pair<CarData, CarData> parents ){
    CarData child;
    std::vector<b2Vec2> child_points;
    for ( int i = 0; i < parents.first.points.size(); i++ ){
        b2Vec2 child_point;
        child_point.x = keepInSpec( mutate( performCrossover( parents.first.points[i].x, parents.second.points[i].x ) ) );
        child_point.y = keepInSpec( mutate( performCrossover( parents.first.points[i].y, parents.second.points[i].y ) ) );
        child_points.push_back( child_point );
    }
    child.points = child_points;
	child.pos = parents.first.pos;
	child.car_density = mutate( performCrossover( parents.first.car_density, parents.second.car_density ) );
    child.car_friction = mutate( performCrossover( parents.first.car_friction, parents.second.car_friction ) );
    child.wheels_indexes = {parents.first.wheels_indexes[0], parents.second.wheels_indexes[1]};
    child.wheels_radiuses = {mutate( performCrossover( parents.first.wheels_radiuses[0], parents.second.wheels_radiuses[0] ) ), mutate( performCrossover( parents.first.wheels_radiuses[1], parents.second.wheels_radiuses[1] ) )};
    for ( auto& wheel_radius : child.wheels_radiuses ){
        if ( wheel_radius < MIN_RADIUS ){
            wheel_radius = MIN_RADIUS;
        }
        if ( wheel_radius > MAX_RADIUS ){
            wheel_radius = MAX_RADIUS;
        }
    }
    child.wheels_density = mutate( performCrossover( parents.first.car_density, parents.second.car_density ) );
	child.wheels_friction = mutate( performCrossover( parents.first.car_friction, parents.second.car_friction ) );
	child.max_speed = -20.0f;
	child.motor_power = 500.0f;
	child.car_color = sf::Color::White;
	child.wheels_color = sf::Color( 128, 128, 128 );
	child.car_color.a = 128;
	child.wheels_color.a = 128;

    return child;
}

float GeneticAlgorithm::mutate( float data ){
    if ( randomFloatGenerator( 0.0, 1.0 ) <= mutation_rate_ ){
        return data * randomNormalFloatGenerator( 1.0, mutation_power_ );
    } else{
        return data;
    }
}

std::pair<CarData, CarData> GeneticAlgorithm::selectParents(){
    double total_fitness = 0.0;
    for ( auto car : population_ ){
        total_fitness += car.second;
        if ( generation_ <= sa_generations_ ){
            total_fitness += ( sa_generations_ - generation_ )/sa_generations_ * saga_temperature_;
        }
    }

    float random_value = randomFloatGenerator( 0.0, total_fitness );
    float select_value = 0.0;
    CarData parent1;
    for ( auto car : population_ ){
        select_value += car.second;
        if ( generation_ < sa_generations_ ){
            select_value += ( sa_generations_ - generation_ )/sa_generations_ * saga_temperature_;
        }
        if ( select_value >= random_value ){
            parent1 = car.first;
            break;
        }
    }

    float random_value2 = randomFloatGenerator( 0.0, total_fitness );
    float select_value2 = 0.0;
    CarData parent2;
    for ( auto car : population_ ){
        select_value2 += car.second;
        if ( generation_ < sa_generations_ ){
            select_value2 += ( sa_generations_ - generation_ )/sa_generations_ * saga_temperature_;
        }
        if ( select_value2 >= random_value2 ){
            parent2 = car.first;
            break;
        }
    }
    return std::make_pair( parent1, parent2 );
}

void GeneticAlgorithm::uploadPopulation( std::vector<std::pair<CarData, float>> up_population ){
    generation_ += 1;
    population_ = up_population;
}

std::vector<Car> GeneticAlgorithm::run(){
    float max_distance = 0.0;
    // Copy elite for the next population
    CarData elite;
    for ( auto car : population_ ){
        if ( car.second > max_distance ){
            elite = car.first;
            max_distance = car.second;
        }
    }
    elite.car_color = sf::Color::Green;
    std::vector<Car> new_population;
    new_population.push_back( createCar( elite ) );
    for ( int i = 0; i < population_.size() - 1; i++ ){
        std::pair<CarData, CarData> parents = selectParents();
        CarData child = crossover( parents );
        Car &&new_car = createCar( child );
        new_population.push_back( new_car );
    }
    return new_population;
}

void GeneticAlgorithm::setGeneration( int gen ){
    generation_ = gen;
}

float GeneticAlgorithm::getCrossoverRate(){
    return crossover_rate_;
}
void GeneticAlgorithm::setCrossoverRate( float new_crossover_rate ){
    crossover_rate_ = new_crossover_rate;
}
float GeneticAlgorithm::getMutationRate(){
    return mutation_rate_;
}
void GeneticAlgorithm::setMutationRate( float new_mutation_rate ){
    mutation_rate_ = new_mutation_rate;
}
float GeneticAlgorithm::getMutationPower(){
    return mutation_power_;
}
void GeneticAlgorithm::setMutationPower( float new_mutation_power ){
    mutation_power_ = new_mutation_power;
}
int GeneticAlgorithm::getSaGens(){
    return sa_generations_;
}
void GeneticAlgorithm::setSaGens( int new_sa_gens ){
    sa_generations_ = new_sa_gens;
}
float GeneticAlgorithm::getSaTemperature(){
    return saga_temperature_;
}
void GeneticAlgorithm::setSaTemperature( float new_sa_temperature ){
    saga_temperature_ = new_sa_temperature;
}