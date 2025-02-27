/*
Jakub Ciarcinski, Eryk Jakubowski
Functions which handle user's interactions with UI.
*/

#include "../include/EventHandlers.h"

void handleClickSavePopulation( std::vector<Car> &cars, GeneticAlgorithm &saga, ScrollableList &file_list ){
    std::vector<CarData> data;
    for ( auto& car: cars ){
        data.push_back( car.data );
    }
    std::ostringstream oss;
    oss << "./saved_generations/" << SEED << "_"<< saga.getGeneration() << ".json";
    std::string path = oss.str();
    saveCarDataToJson( data, path );
    file_list.setItems( getFilesInDirectory( "./saved_generations" ) ); // Get files from current directory.
    std::cout << "Population saved!" << std::endl;
}

void handleClickLoadPopulation( std::vector<Car> &cars, GeneticAlgorithm &saga, ScrollableList &file_list, std::vector<Box> &boxes, std::vector<std::vector<std::pair<float, float>>> &cars_positions ){
    std::vector<CarData> data;
    std::vector<std::pair<float, float>> blank;
    std::string selected_file = file_list.getHighlightedItemName();
    std::string path = "./saved_generations/" + selected_file;
    if ( path.size() > 21 ){
        loadCarDataFromJson( data, path );
        for ( auto& car : cars ){
            car.destroy();
        }
        cars.clear();
        size_t underscore_pos = selected_file.find( '_' );
        if ( underscore_pos != std::string::npos ){
            SEED = std::stoi( selected_file.substr( 0, underscore_pos ) );
            createGround( boxes, -300, 400, 150, 10, 150, sf::Color::Green );
            saga.setGeneration( std::stoi( selected_file.substr( underscore_pos + 1 ) ) );
        } else{
            std::cerr << "Invalid format: underscore not found" << std::endl;
        }
    }
    for ( auto &car_data : data ){
        car_data.car_color = sf::Color::White;
        car_data.wheels_color = sf::Color( 128, 128, 128 );

        cars_positions.push_back( blank );

        car_data.car_color.a = 128;
        car_data.wheels_color.a = 128;
        cars.push_back( createCar( car_data ) );
    }
    data.clear();
    std::cout << "Population loaded!" << std::endl;
}

void handleClickSet( std::vector<Car> &cars, GeneticAlgorithm &saga, std::vector<Box> &boxes, std::vector<std::vector<std::pair<float, float>>> &cars_positions, std::vector<float> &boxes_x,
                    std::vector<float> &boxes_y, TextField fields[], std::vector<sf::Text> &labels, std::vector<CarData> &cars_data, float &track_start, float &track_end ){
    if ( SEED != std::stoi( fields[0].getInput() ) && isInteger( fields[0].getInput() ) ){
        SEED = std::stoi( fields[0].getInput() );
        init( boxes, boxes_x, boxes_y, cars, cars_data, cars_positions, track_start, track_end );
        labels[0].setString( "Generation: 0" );
        saga.setGeneration( 0 );
    }
    if ( isFloat( fields[1].getInput() ) ){
        GRAVITY = std::stof( fields[1].getInput() );
        world.SetGravity( b2Vec2( 0, -GRAVITY ) );
    }
    if ( isFloat( fields[2].getInput() ) ){
        saga.setMutationRate( std::stof( fields[2].getInput() ) );
    }
    if ( isFloat( fields[3].getInput() ) ){
        saga.setMutationPower( std::stof( fields[3].getInput() ) );
    }
    if ( isFloat( fields[4].getInput() ) ){
        saga.setCrossoverRate( std::stof( fields[4].getInput() ) );
    }
    if ( isInteger( fields[5].getInput() ) ){
        saga.setSaGens( std::stoi( fields[5].getInput() ) );
    }
    if ( isFloat( fields[6].getInput() ) ){
        saga.setSaTemperature( std::stof( fields[6].getInput() ) );
    }
}