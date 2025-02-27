/*
Eryk Jakubowski
A class that represents an UI Scrollable list of interactive items.
*/

#include "../include/ScrollableList.h"

ScrollableList::ScrollableList( float x, float y, float width, float height )
    : position_( x, y ), size_( width, height ), scroll_offset_( 0 ), selected_item_index_( -1 ){
    box_.setPosition( x, y );
    box_.setSize( sf::Vector2f( width, height ) );
    box_.setFillColor( sf::Color::White );
    box_.setOutlineThickness( 2 );
    box_.setOutlineColor( sf::Color::Black );

    font_.loadFromFile( "arial.ttf" );
    scroll_bar_.setSize( sf::Vector2f( 20, WINDOW_HEIGHT * 0.05f ) );
    scroll_bar_.setPosition( x + width - 20, y );
    scroll_bar_.setFillColor( sf::Color::Red );
}

void ScrollableList::setItems( const std::vector<std::string>& items ){
    this->items_ = items;
    scroll_offset_ = 0; // Reset scroll position.
    updateView();
}

void ScrollableList::handleEvent( sf::Event& event, const sf::View& view, sf::RenderWindow& window ){
if ( event.type == sf::Event::MouseWheelScrolled ){
    if ( event.mouseWheelScroll.delta > 0 ){
        scroll_offset_ = std::max( scroll_offset_ - 1, 0 );
    } else if ( event.mouseWheelScroll.delta < 0 ){
        scroll_offset_ = std::min( scroll_offset_ + 1, static_cast<int>( items_.size() ) - static_cast<int>( visible_items_count_ ) );
    }
    updateView();
} else if ( event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left ){
    sf::Vector2i mouse_pos_window = sf::Mouse::getPosition( window );
    sf::Vector2f mouse_pos_view = window.mapPixelToCoords( mouse_pos_window, view );
    for ( size_t i = 0; i < visible_items_.size(); ++i ){
        if ( visible_items_[i].getGlobalBounds().contains( mouse_pos_view ) ){
            // Deselect previously selected item.
            if ( selected_item_index_ != -1 ){
                visible_items_[selected_item_index_].setFillColor( sf::Color::Black );
            }
            selected_item_index_ = scroll_offset_ + i;
            updateView(); // Update appearance.
            std::cout << "Selected item: " << items_[selected_item_index_] << std::endl;
            break;
        }
    }
}
}

void ScrollableList::draw( sf::RenderWindow& window ){
    window.draw( box_ );

    for ( const auto& text : visible_items_ ){
        window.draw( text );
    }

    window.draw( scroll_bar_ );
}

std::string ScrollableList::getHighlightedItemName(){
    if ( selected_item_index_ >= 0 && selected_item_index_ < items_.size() ){
        return items_[selected_item_index_];
    } else{
        return ""; // Return an empty string if no item is highlighted.
    }
}

void ScrollableList::updateView(){
    // Calculate the visible ratio of items.
    float visible_ratio = static_cast<float>( visible_items_count_ ) / items_.size();

    // Check if scrollbar should be visible.
    if ( visible_ratio < 1.0f ){
        // Set the scrollbar's size.
        float scroll_bar_height = size_.y * visible_ratio;
        scroll_bar_.setSize( sf::Vector2f( 20, scroll_bar_height ) );

        // Calculate the scrollbar's position.
        float scroll_bar_y = position_.y + ( size_.y - scroll_bar_height ) * ( scroll_offset_ / static_cast<float>( items_.size() - visible_items_count_ ) );
        scroll_bar_.setPosition( position_.x + size_.x - 20, scroll_bar_y );
        scroll_bar_.setFillColor( sf::Color::Red );
        scroll_bar_.setOutlineColor( sf::Color::Black );
        scroll_bar_.setOutlineThickness( 1.0f );

        // Calculate the first and last visible item index.
        unsigned int first_visible_item = scroll_offset_;
        unsigned int last_visible_item = std::min( scroll_offset_ + visible_items_count_, static_cast<unsigned int>( items_.size() ) );

        // Populate the visible_items vector.
        visible_items_.clear();
        for ( unsigned int i = first_visible_item; i < last_visible_item; ++i ){
            sf::Text text( items_[i], font_, 20 );
            text.setFillColor( sf::Color::Black );
            text.setPosition( position_.x + 5, position_.y + 5 + ( i - scroll_offset_ ) * 10 );
            visible_items_.push_back( text );
        }
    } else{
        // Hide the scrollbar if not enough items to scroll.
        scroll_bar_.setSize( sf::Vector2f( 0, 0 ) );

        // Populate the visible_items vector with all items.
        visible_items_.clear();
        for ( unsigned int i = 0; i < items_.size(); ++i ){
            sf::Text text( items_[i], font_, 20 );
            text.setFillColor( sf::Color::Black );
            text.setPosition( position_.x + 5, position_.y + 5 + i * 20 );
                        // Highlight the selected item.
            if ( static_cast<int>( i ) == selected_item_index_ ){
                // Change the background color or add a border to indicate selection.
                text.setFillColor( sf::Color::Red );
            }
            visible_items_.push_back( text );
        }
    }
}

void ScrollableList::setWindow( sf::RenderWindow* win ){
    window_ = win;
}