/*
Eryk Jakubowski
A class that represents a genetic algorithm with its parameters and performs selection, crossover and mutation on its population each generation.
*/

#pragma once
#include "./Car.h"
#include "./Utils.h"

class GeneticAlgorithm{
public:
    GeneticAlgorithm( float mutation_rate, float mutation_power, float crossover_rate ,int sa_generations, float saga_temperature ) :
        mutation_rate_( mutation_rate ),
        mutation_power_( mutation_power ),
        crossover_rate_( crossover_rate ),
        sa_generations_( sa_generations ),
        saga_temperature_( saga_temperature )
    {};

    float performCrossover( float data1, float data2 );
    std::vector<Car> run();
    float keepInSpec( float data );

    int getGeneration();
    void setGeneration( int gen );

    float getCrossoverRate();
    void setCrossoverRate( float new_crossover_rate );

    float getMutationRate();
    void setMutationRate( float new_mutation_rate );

    float getMutationPower();
    void setMutationPower( float new_mutation_power );

    int getSaGens();
    void setSaGens( int new_sa_gens );

    float getSaTemperature();
    void setSaTemperature( float new_sa_temperature );

    void uploadPopulation( std::vector<std::pair<CarData, float>> up_population );
private:
    std::vector<std::pair<CarData, float>> population_;
    float mutation_rate_;
    float mutation_power_;
    float crossover_rate_;
    int generation_ = 0;
    int sa_generations_;
    float saga_temperature_;
    CarData crossover( std::pair<CarData, CarData> parents );
    float mutate( float data );
    std::pair<CarData, CarData> selectParents();
};