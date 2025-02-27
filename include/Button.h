/*
Jakub Ciarcinski, Eryk Jakubowski
A struct that represents an UI Button with text.
*/

#pragma once
#include "./Globals.h"

class Button {
public:
    Button( float x, float y, float width, float height, const std::string& text, const sf::Font& font );

    void draw( sf::RenderWindow& window );

    bool isClicked( sf::Vector2i mouse_pos );

    void isMouseOver( sf::RenderWindow& window, sf::View& view ); // Changes color of the button on hover.

private:
    sf::RectangleShape button_shape_;
    sf::Text button_text_;
};
