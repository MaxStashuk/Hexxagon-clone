#include "Menu.h"
//Class for UI of menu

Menu::Menu(sf::RenderWindow* window, sf::Font font){
    this->window = window;
    this->font = font;
    this->playVsFriend = Button(sf::Vector2f (1400, 200), sf::Vector2f (100, 300),
                                 this->font,"Play vs friend", 68);
    this->loadGame = Button(sf::Vector2f(600, 200),sf::Vector2f(100, 600),
                             this->font, "Load game",68);
    this->bestGame = Button(sf::Vector2f(600, 200), sf::Vector2f(900, 600),
                             this->font, "Best games", 68);
    this->exitMenu = Button(sf::Vector2f(300, 100), sf::Vector2f(1200, 825),
                                this->font, "Exit Game", 48);
}



void Menu::eventHandler(Controller& c){
    sf::Event event;
    while(this->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->window->close();
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(*this->window);
                if (this->playVsFriend.isClickable(mousePosition)) {
                   std::cout << "GAME VS FRIEND IS OPENED\n";
                   c.setState(STATE::GAME_VS_FRIEND);
                   break;
               } else if (this->loadGame.isClickable(mousePosition)) {
                   std::cout << "LOADING MENU IS OPENED\n";
                   c.setState(STATE::LOAD_GAME);
                   break;
               } else if (this->bestGame.isClickable(mousePosition)) {
                   std::cout << "BEST GAME IS OPENED\n";
                   c.setState(STATE::BEST_GAME);
                   break;
               } else if (this->exitMenu.isClickable(mousePosition)) {
                   this->window->close();
                   std::cout << "Exited the menu! bye bye!\n";
               }
            }
        } else if (event.type == sf::Event::MouseMoved) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(*this->window);
            this->playVsFriend.isClickable(mousePosition);
            this->loadGame.isClickable(mousePosition);
            this->bestGame.isClickable(mousePosition);
            this->exitMenu.isClickable(mousePosition);
        }
    }
}

void Menu::draw() {
    //adding the main menu sign
    sf::Text mainSign ("Main Menu", this->font);
    mainSign.setCharacterSize(68);
    mainSign.setFillColor(Colors::Sign);
    auto mainSignBounds = mainSign.getLocalBounds();
    mainSign.setOrigin(mainSignBounds.width / 2.f,0);
    mainSign.setPosition(800, 100);

    this->window->draw(mainSign);
    this->playVsFriend.draw(this->window);
    this->loadGame.draw(this->window);
    this->bestGame.draw(this->window);
    this->exitMenu.draw(this->window);
}
