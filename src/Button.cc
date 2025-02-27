/*
Jakub Ciarcinski, Eryk Jakubowski
A struct that represents an UI Button with text.
*/

#include "../include/Button.h"

Button::Button( float x, float y, float width, float height, const std::string& text, const sf::Font& font ){
    // Set up the button rectangle.
    button_shape_.setPosition( x, y );
    button_shape_.setSize( sf::Vector2f( width, height ) );
    button_shape_.setOutlineColor( sf::Color::Green );
    button_shape_.setOutlineThickness( 4 );

    // Set up the text.
    button_text_.setFont( font );
    button_text_.setString( text );
    button_text_.setCharacterSize( 20 );
    button_text_.setFillColor( sf::Color::Black );
    // Center the text on the button.
    sf::FloatRect text_rect = button_text_.getLocalBounds();
    button_text_.setOrigin( text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f );
    button_text_.setPosition( 
        button_shape_.getPosition().x + button_shape_.getSize().x / 2.0f,
        button_shape_.getPosition().y + button_shape_.getSize().y / 2.0f
     );
}

void Button::draw( sf::RenderWindow& window ){
    window.draw( button_shape_ );
    window.draw( button_text_ );
}

// Changes color of the button on hover.
void Button::isMouseOver( sf::RenderWindow& window, sf::View& view ){
    sf::Vector2i mouse_pos_window = sf::Mouse::getPosition( window );
    sf::Vector2f mouse_pos_view = window.mapPixelToCoords( mouse_pos_window, view );
    sf::FloatRect bounds = button_shape_.getGlobalBounds();
    if ( bounds.contains( static_cast<sf::Vector2f>( mouse_pos_view ) ) ){
        button_shape_.setFillColor( sf::Color::Red );
    } else{
        button_shape_.setFillColor( sf::Color::Green );
    }
}

bool Button::isClicked( sf::Vector2i mouse_pos ){
    return button_shape_.getGlobalBounds().contains( static_cast<sf::Vector2f>( mouse_pos ) );
}
