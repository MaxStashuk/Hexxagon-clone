#include "Button.h"

Button::Button() {
}

Button::Button(sf::Vector2f bodySize, sf::Vector2f position, sf::Font& font, const std::string& text, int charSize) {
    //initializing the body of the button
    this->body = sf::RectangleShape(bodySize);
    this->body.setPosition(position);
    this->body.setFillColor(Colors::ButtonBody);

    //initializing the sign
    this->text = sf::Text(text, font);
    this->text.setCharacterSize(charSize);
    this->text.setFillColor(Colors::Sign);

    //putting the sign to the centre
    auto textBounds = this->text.getGlobalBounds();
    auto bodyBounds = this->body.getGlobalBounds();
    this->text.setPosition( (position.x + bodyBounds.width / 2.f) - (textBounds.width / 2.f),
                            (position.y + bodyBounds.height / 2.f) - textBounds.height);

}
Button::Button(sf::Vector2f bodySize, sf::Vector2f position, const std::string& text, int charSize){
    this->body = sf::RectangleShape(bodySize);
    this->body.setPosition(position);
    this->body.setFillColor(Colors::ButtonBody);

    //init the font
    sf::Font font;
    if(!font.loadFromFile("assets/consola.ttf")){
        std::cout<<"ERROR::Controller:: failed to init the font\n";
        return;
    }

    //initializing the sign
    this->text = sf::Text(text, font);
    this->text.setCharacterSize(charSize);
    this->text.setFillColor(Colors::Sign);

    //putting the sign to the centre
    auto textBounds = this->text.getGlobalBounds();
    auto bodyBounds = this->body.getGlobalBounds();
    this->text.setPosition( (position.x + bodyBounds.width / 2.f) - (textBounds.width / 2.f),
                            (position.y + bodyBounds.height / 2.f) - textBounds.height);
}

void Button::draw(sf::RenderWindow* window){
    window->draw(this->body);
    window->draw(this->text);
}

bool Button::isClickable(const sf::Vector2i& mousePosition) {
    if (this->body.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
        this->body.setFillColor(Colors::SelectedButtonBody);
        this->text.setFillColor(Colors::SelectedSign);
        return true;
    } else {
        this->body.setFillColor(Colors::ButtonBody);
        this->text.setFillColor(Colors::Sign);
        return false;
    }
}