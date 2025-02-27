/*
Jakub Ciarcinski
Functions which draw all given objects every frame.
*/

#include "../include/Render.h"

void render( sf::RenderWindow &w, std::vector<Box> &boxes ){
	w.clear( sf::Color::White );

	// Draw all rectangles.
	for ( const auto &box : boxes ){
		sf::RectangleShape rect;
		rect.setPosition( box.body->GetPosition().x * SCALE, WINDOW_HEIGHT - ( box.body->GetPosition().y * SCALE ) );
		rect.setOrigin( box.width / 2, box.height / 2 );
		rect.setSize( sf::Vector2f( box.width, box.height ) );
		rect.setRotation( -1 * box.body->GetAngle() * DEG_PER_RAD );
		rect.setFillColor( box.color );
		w.draw( rect );
	}
}

void renderCar( sf::RenderWindow &w, Car &car ){
	// Draw wheels.
	for ( const auto &wheel : car.wheels ){
		sf::CircleShape circ( wheel.radius );
		circ.setOrigin( circ.getRadius(), circ.getRadius() );
		circ.setOutlineColor( sf::Color::Black );
		circ.setOutlineThickness( -1 );
		circ.setPosition( wheel.body->GetPosition().x * SCALE, WINDOW_HEIGHT - ( wheel.body->GetPosition().y * SCALE ) );
		circ.setFillColor( wheel.color );
		w.draw( circ );

		// Draw radius.
		sf::Vertex line[] =
		{
			sf::Vertex( sf::Vector2f( wheel.body->GetPosition().x * SCALE, WINDOW_HEIGHT - ( wheel.body->GetPosition().y * SCALE ) ), sf::Color::Black ),
			sf::Vertex( sf::Vector2f( wheel.body->GetPosition().x * SCALE + wheel.radius * std::cos( wheel.body->GetAngle() ), WINDOW_HEIGHT - ( wheel.body->GetPosition().y * SCALE ) - wheel.radius * std::sin( wheel.body->GetAngle() ) ), sf::Color::Black )
		};
		w.draw( line, 2, sf::Lines );
	}
	sf::ConvexShape triang;
	triang.setPointCount( 3 );
	triang.setFillColor( car.data.car_color );

	b2Fixture* fixture = car.body->GetFixtureList();

	// Draw car's body.
	while ( fixture != nullptr ){
		const b2PolygonShape* shape = dynamic_cast<const b2PolygonShape*>( fixture->GetShape() );
		if ( shape != nullptr ){
			for ( int i = 0; i < 3; ++i ){
			b2Vec2 vertex = car.body->GetWorldPoint( shape->m_vertices[i] );
			triang.setPoint( i, sf::Vector2f( vertex.x * SCALE, WINDOW_HEIGHT - ( vertex.y * SCALE ) ) );
		}
		}
		triang.setOutlineColor( sf::Color::Black );
		triang.setOutlineThickness( -1 );

		w.draw( triang );
		fixture = fixture->GetNext();
	}
}

void drawPlot( sf::RenderWindow& window, const sf::Vector2f& position, const std::vector<float>& x_data, const std::vector<float>& y_data, const sf::Color& color ){
    sf::VertexArray plot( sf::LineStrip );

    for ( size_t i = 0; i < x_data.size(); ++i ){
        plot.append( sf::Vertex( sf::Vector2f( position.x + x_data[i], position.y - y_data[i] ), color ) );
    }

    window.draw( plot );
}