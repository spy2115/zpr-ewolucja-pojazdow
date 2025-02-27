/*
Eryk Jakubowski
A class that represents an UI Scrollable list of interactive items.
*/

#pragma once
#include "./Globals.h"
#include <iostream>

class ScrollableList {
public:
    ScrollableList( float x, float y, float width, float height );
    void setItems( const std::vector<std::string>& items );
    void handleEvent( sf::Event& event, const sf::View& view, sf::RenderWindow& window );
    void draw( sf::RenderWindow& window );
	std::string getHighlightedItemName();
    void updateView();
    void setWindow( sf::RenderWindow* win );

private:
    sf::RectangleShape box_;
    sf::RectangleShape scroll_bar_;
    sf::Font font_;
    sf::RenderWindow* window_;
    std::vector<std::string> items_;
    std::vector<sf::Text> visible_items_;
    sf::Vector2f position_;
    sf::Vector2f size_;
    unsigned int visible_items_count_ = 10;
    int scroll_offset_;
    int selected_item_index_; // Index of the selected item ( -1 if none selected )
};