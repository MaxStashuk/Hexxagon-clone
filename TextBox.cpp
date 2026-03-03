#include "TextBox.h"

TextBox::TextBox() {

}

TextBox::TextBox(sf::Vector2f bodySize, sf::Vector2f pos, std::string input, sf::Font &font, int chSize) {
    this->body = sf::RectangleShape(bodySize);
    this->body.setPosition(pos);
    this->body.setFillColor(Colors::Background);
    this->body.setOutlineColor(Colors::ButtonBody);
    this->body.setOutlineThickness(7);
    this->text = sf::Text(input, font);
    this->text.setFillColor(Colors::Sign);
    this->text.setCharacterSize(chSize);

    auto textBounds = this->text.getGlobalBounds();
    auto bodyBounds = this->body.getGlobalBounds();

    this->text.setPosition(pos.x + 10,
                           pos.y + bodyBounds.height / 2.f - textBounds.height - 50);
}


void TextBox::draw(sf::RenderWindow *window) {
    window->draw(this->body);
    window->draw(this->text);
}

void TextBox::setString(std::string str){
    this->text.setString(str);
}

std::string TextBox::getString(){
    return this->text.getString();
}


