/*
Jakub Ciarcinski
Functions which draw all given objects every frame.
*/

#pragma once
#include "./Car.h"

void render( sf::RenderWindow &w, std::vector<Box> &boxes );
void renderCar( sf::RenderWindow &w, Car &car );
void drawPlot( sf::RenderWindow& window, const sf::Vector2f& position, const std::vector<float>& x_data, const std::vector<float>& y_data, const sf::Color& color );