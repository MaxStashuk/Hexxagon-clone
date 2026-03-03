#include "Hex.h"

Hex::Hex() {
    this->pawn = PAWN::NONE;
    this->coord = {0,0};
    this->body = sf::CircleShape(45, 6);
    this->body.rotate(90);
    auto bodyBounds = this->body.getLocalBounds();
    this->body.setOrigin(bodyBounds.width/2.f, bodyBounds.height/2);
    this->body.setFillColor(Colors::HexBody);
    this->body.setOutlineColor(Colors::HexOutline);
    this->body.setOutlineThickness(5);
}

void Hex::draw(sf::RenderWindow* window){
    window->draw(this->body);
    window->draw(drawPawn());
}

void Hex::setCoords(int x, int y){
    this->coord = {x, y};
}

std::pair<int, int> Hex::getCoords(){
    return this->coord;
}

void Hex::setPawn(PAWN p){
    this->pawn = p;
}

sf::CircleShape Hex::drawPawn(){
    auto tmp = sf::CircleShape(30);
    auto tmpBounds = tmp.getLocalBounds();
    tmp.setOrigin(tmpBounds.width/2.f, tmpBounds.height/2.f);
    tmp.setPosition(this->body.getPosition().x, this->body.getPosition().y + 5);
    switch(this->pawn){
        case PAWN::BLUE:
            tmp.setFillColor(Colors::BluePawn);
            break;
        case PAWN::RED:
            tmp.setFillColor(Colors::RedPawn);
            break;
        case PAWN::NONE:
            tmp.setFillColor(Colors::HexBody);
            break;
    }
    return tmp;
}

sf::Vector2f Hex::coordsToPos(){
    float xCord = this->coord.first;
    float yCord = this->coord.second;
    float sze = 55.f;
    float xOff = 470.f;
    float yOff = 110.f;

    float xPos = sze * 3.f / 2.f * xCord + xOff;
    float yPos = sze * sqrt(3.f) * (yCord + 0.5f * ((int)xCord & 1) ) + yOff;
    return sf::Vector2f(xPos, yPos);
}

PAWN Hex::getPawn() {
    return this->pawn;
}

void Hex::setPosition(sf::Vector2f position){
    this->body.setPosition(position);
}

sf::Vector2f Hex::getPosition(){
    return this->body.getPosition();
}

bool Hex::isClickable(sf::Vector2i& mousePosition, bool toMove) {
    return this->body.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))
           && ((this->pawn == PAWN::RED && toMove) || (this->pawn == PAWN::BLUE && !toMove));
}

bool Hex::isClickable(sf::Vector2i& mousePosition) {
    return this->body.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))
           && this->pawn == PAWN::NONE && this->pawn != PAWN::UNACTIVE;
}

void Hex::update(sf::Color c) {
    this->body.setOutlineColor(c);
}

void Hex::setDefaultOutline() {
    this->body.setOutlineColor(Colors::HexOutline);
}

sf::Vector3i Hex::offsetToCube(sf::Vector2i offset){
    auto x = offset.x;
    auto z = offset.y - (x - (x&1)) / 2;
    auto y = -x-z;
    return sf::Vector3i(x, y, z);
}

int Hex::distance(Hex hex){
    auto thisCoords = sf::Vector2i (this->getCoords().first, this->getCoords().second);
    auto hexCoords = sf::Vector2i (hex.getCoords().first, hex.getCoords().second);
    auto a = this->offsetToCube(thisCoords);
    auto b = hex.offsetToCube(hexCoords);

    return std::max(abs(a.x - b.x), std::max(abs(a.y - b.y), abs(a.z - b.z)));
}


