/*
Eryk Jakubowski
A class that represents an interactive input text field.
*/

#pragma once
#include "./Globals.h"

class TextField {
public:
    TextField( float x, float y, float width, float height, const sf::Font& font );

    void draw( sf::RenderWindow& window );
    void handleEvent( sf::Event& event, const sf::View& view, sf::RenderWindow& window );
    std::string getInput();
	void setInitialText( std::string initial_text );
private:
    sf::RectangleShape box_;
    sf::Text text_;
    std::string input_;
    bool has_focus_;
};