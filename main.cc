/*
Eryk Jakubowski, Jakub Ciarcinski
Main function of our project, all objects are generated there, also contains the Game Loop.
*/

#include <iostream>
#include "./include/Button.h"
#include "./include/TextField.h"
#include "./include/Utils.h"
#include "./include/EventHandlers.h"

int main(){ 
	// Setup SFML window.
	sf::RenderWindow w( sf::VideoMode( WINDOW_WIDTH, WINDOW_HEIGHT ), "Ewolucja pojazdów w 2D" );
	w.setPosition( sf::Vector2i( 100, 50 ) );
	w.setFramerateLimit( 60 );
	sf::View view1, view2, view3;
	view1.setViewport( sf::FloatRect( 0, 0, 0.7f, 0.7f ) );
	view1.setSize( WINDOW_WIDTH , WINDOW_HEIGHT );
	view2.setViewport( sf::FloatRect( 0.7f, 0, 0.3f, 1.0f ) );
	view2.setSize( WINDOW_WIDTH * 0.3f, WINDOW_HEIGHT );
	view2.setCenter( WINDOW_WIDTH * 0.15f, WINDOW_HEIGHT / 2.0f );
	view3.setViewport( sf::FloatRect( 0, 0.7f, 0.7f, 0.3f ) );
	view3.setCenter( WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 );
	view3.setSize( WINDOW_WIDTH, WINDOW_HEIGHT );
	std::vector<Box> boxes;
	std::vector<float> boxes_x;
	std::vector<float> boxes_y;
	std::vector<Car> cars;
	std::vector<CarData> cars_data;
	std::vector<std::vector<std::pair<float, float>>> cars_positions;
	float track_start;
	float track_end;
	init( boxes, boxes_x, boxes_y, cars, cars_data, cars_positions, track_start, track_end );

	sf::Font font;
    if ( !font.loadFromFile( "arial.ttf" ) ) { 
        std::cerr << "Error loading font\n";
        return -1;
    }
	std::vector<Button> buttons;
	Button save_population( 0.15 * WINDOW_WIDTH - 100, 20, 200, 36, "Zapisz populacje", font );
	Button load_population( 0.15 * WINDOW_WIDTH - 100, 70, 200, 36, "Wczytaj populacje", font );
	Button set( 0.15 * WINDOW_WIDTH - 100, 820, 200, 36, "Zapisz", font );
	buttons.push_back( save_population );
	buttons.push_back( load_population );
	buttons.push_back( set );
	
	GeneticAlgorithm saga( 0.1, 0.1, 0.9, 20, 100.0 );
	
	ScrollableList file_list( 0.15 * WINDOW_WIDTH - 100, 120, 200, WINDOW_HEIGHT * 0.3 );
    file_list.setWindow( &w );
    file_list.setItems( getFilesInDirectory( "./saved_generations" ) );

	sf::Text generation_label( "Generation: 0", font, 20 );
	generation_label.setPosition( 0.15 * WINDOW_WIDTH - 100, 0 );
	generation_label.setFillColor( sf::Color::Black );

	TextField seed_field( 0.15 * WINDOW_WIDTH - 100, 420, 200, 30, font );
	seed_field.setInitialText( std::to_string( SEED ) );
    TextField gravity_field( 0.15 * WINDOW_WIDTH - 100, 480, 200, 30, font );
	gravity_field.setInitialText( std::to_string( GRAVITY ) );
	TextField mutation_rate_field( 0.15 * WINDOW_WIDTH - 100, 540, 200, 30, font );
	mutation_rate_field.setInitialText( std::to_string( saga.getMutationRate() ) );
	TextField mutation_power_field( 0.15 * WINDOW_WIDTH - 100, 600, 200, 30, font );
	mutation_power_field.setInitialText( std::to_string( saga.getMutationPower() ) );
	TextField crossover_field( 0.15 * WINDOW_WIDTH - 100, 660, 200, 30, font );
	crossover_field.setInitialText( std::to_string( saga.getCrossoverRate() ) );
	TextField sa_gen_field( 0.15 * WINDOW_WIDTH - 100, 720, 200, 30, font );
	sa_gen_field.setInitialText( std::to_string( saga.getSaGens() ) );
	TextField sa_temp_field( 0.15 * WINDOW_WIDTH - 100, 780, 200, 30, font );
	sa_temp_field.setInitialText( std::to_string( saga.getSaTemperature() ) );
	TextField fields[] = { seed_field, gravity_field, mutation_rate_field, mutation_power_field, crossover_field, sa_gen_field, sa_temp_field };
	std::string label_names[] = { "Seed:", "Gravity:", "Mutation Rate:", "Mutation Power:", "Crossover Rate:", "SA Generations:", "SA Temperature:" };
	std::vector<sf::Text> labels;
	labels.push_back( generation_label );

	int y_start = 390;
	for ( std::string label_name : label_names ){
		sf::Text label( label_name, font, 20 );
		label.setPosition( 0.15 * WINDOW_WIDTH - 100, y_start );
		label.setFillColor( sf::Color::Black );
		labels.push_back( label );
		y_start += 60;
	}
	
	/** GAME LOOP **/
	std::vector<std::pair<CarData, float>> new_cars_data;
	while ( w.isOpen() ){
        sf::Event event;
        while ( w.pollEvent( event ) ){
            if ( event.type == sf::Event::Closed ){
				w.close();
			}
			for ( auto &field : fields ){
				field.handleEvent( event, view2, w );
			}
			if ( event.type == sf::Event::MouseButtonPressed ){
				file_list.handleEvent( event, view2, w );
				
                if ( event.mouseButton.button == sf::Mouse::Left ){
					sf::Vector2f mouse_pos_view_float = w.mapPixelToCoords( sf::Mouse::getPosition( w ), view2 );
					sf::Vector2i mouse_pos_view( mouse_pos_view_float.x, mouse_pos_view_float.y );
                    if ( save_population.isClicked( mouse_pos_view ) ){
						handleClickSavePopulation( cars, saga, file_list );
                    }
					if ( load_population.isClicked( mouse_pos_view ) ){
						handleClickLoadPopulation( cars, saga, file_list, boxes, cars_positions );
                    }
					if ( set.isClicked( mouse_pos_view ) ){
						handleClickSet( cars, saga, boxes, cars_positions, boxes_x, boxes_y, fields, labels, cars_data, track_start, track_end );
                    }
                }
			}
        }
		float max_distance = 0;
		for ( auto& car : cars ){
			if ( car.getPosition().x > max_distance && car.counter < 600 / SPEED ){
				b2Vec2 pos = car.getPosition();
				max_distance = pos.x;
				view1.setCenter( pos.x * SCALE, WINDOW_HEIGHT - ( ( pos.y ) * SCALE ) );
			}
		}
		w.clear();
		w.setView( view1 );
		world.Step( SPEED / 60.f, 6, 3 );
		render( w, boxes );
		int stuck_cars = 0;
		for ( auto& car : cars ){
			if ( car.traveled_distance < car.getPosition().x ){
				car.traveled_distance = car.getPosition().x;
			}
			if ( !car.isStuck() ){
				renderCar( w, car );
			} else{
				stuck_cars += 1;
			}
		}
		if ( stuck_cars == cars.size() ){
			for ( auto car : cars ){
				new_cars_data.push_back( car.dumpData() );
			}
			saga.uploadPopulation( new_cars_data );
			labels[0].setString( "Generation: " + std::to_string( saga.getGeneration() ) );
			for ( auto& car : cars ){
				car.destroy();
			}
			cars.clear();
			cars = saga.run();
			new_cars_data.clear();
		}
		w.setView( view2 );
		for ( auto &button : buttons ){
			button.draw( w );
			button.isMouseOver( w, view2 );
		}
		for ( auto &label : labels ){
			w.draw( label );
		}
		for ( auto &field : fields ){
			field.draw( w );
		}

		drawPlot( w, sf::Vector2f( 0.0f, 0.0f ), { 1.0f, 1.0f }, { 0.0f, -1.0f * WINDOW_HEIGHT }, sf::Color::Blue );
		drawPlot( w, sf::Vector2f( 0.0f, 0.0f ), { WINDOW_WIDTH * 1.0f, WINDOW_WIDTH * 1.0f }, { 0.0f, -1.0f * WINDOW_HEIGHT }, sf::Color::Black );
		file_list.draw( w );
		w.setView( view3 );
		for ( auto& car: cars ){
			if ( car.counter < 600 / SPEED ){
				float current_x = ( car.traveled_distance - track_start ) * WINDOW_WIDTH / track_end;
				drawPlot( w, sf::Vector2f( -30.0f, 0.0f ), { current_x, current_x }, { 0.0f, -1.0f * WINDOW_HEIGHT }, sf::Color::Black );
			}
		}
		drawPlot( w, sf::Vector2f( -30.0f, view3.getSize().y / 2 ), boxes_x, boxes_y, sf::Color::Green );
		drawPlot( w, sf::Vector2f( 0.0f, 1.0f ), { -300, WINDOW_WIDTH * 1.0f }, { 0.0f, 0.0f }, sf::Color::Black );
		drawPlot( w, sf::Vector2f( 0.0f, view3.getSize().y ), { -300.0f, WINDOW_WIDTH * 1.0f }, { 0.0f, 0.0f }, sf::Color::Red );
        w.display();
	}
	return 0;
}
