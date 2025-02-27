/*
Eryk Jakubowski
A class that represents an interactive input text field.
*/

#include "../include/TextField.h"

TextField::TextField( float x, float y, float width, float height, const sf::Font& font )
        : has_focus_( false ){
        box_.setPosition( x, y );
        box_.setSize( sf::Vector2f( width, height ) );
        box_.setFillColor( sf::Color::White );
        box_.setOutlineThickness( 1 );
        box_.setOutlineColor( sf::Color::Black );
        text_.setFont( font );
        text_.setCharacterSize( 20 );
        text_.setFillColor( sf::Color::Black );
        text_.setPosition( x + 5, y + 5 );
    }

void TextField::draw( sf::RenderWindow& window ){
    window.draw( box_ );
    window.draw( text_ );
}

void TextField::handleEvent( sf::Event& event, const sf::View& view, sf::RenderWindow& window ){
    if ( event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left ){
        sf::Vector2i mouse_pos_window = sf::Mouse::getPosition( window );
        sf::Vector2f mouse_pos_view = window.mapPixelToCoords( mouse_pos_window, view );
        if ( box_.getGlobalBounds().contains( mouse_pos_view ) ){
            has_focus_ = true;
        } else{
            has_focus_ = false;
        }
    }

    if ( has_focus_ && event.type == sf::Event::TextEntered ){
        if ( event.text.unicode == 8 ){ // Handle backspace.
            if ( !input_.empty() ){
                input_.pop_back();
            }
        } else if ( event.text.unicode < 128 ){ // Handle ASCII input.
            input_ += static_cast<char>( event.text.unicode );
        }
        text_.setString( input_ );
    }
}

std::string TextField::getInput(){
    return input_;
}

void TextField::setInitialText( std::string initial_text ){
    input_ = initial_text;
    text_.setString( input_ );
}