#include "Controller.h"

//THE MAIN CLASS TO CONTROL EVERYTHING

Controller::Controller(){
    this->initWindow();
    this->initFont();
    this->state = STATE::MENU;
}

void Controller::initWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(1600, 1000),
                                        "Hexxagon",
                                        sf::Style::Default);
}

void Controller::initFont() {
    if(!this->font.loadFromFile("assets/consola.ttf")){
        std::cout<<"ERROR::Controller:: failed to init the font\n";
    }
}

void Controller::run() {
    Menu menu = Menu(this->window, this->font);
    Game game = Game(this->window);
    BestGame bestGame = BestGame(this->window);
    LoadGame loadGame = LoadGame(this->window);
    while (this->window->isOpen()) {
        switch (this->state) {
            case STATE::MENU:
                menu.eventHandler(*this);

                // Clear the window
                this->window->clear(Colors::Background);
                // Draw the menu
                menu.draw();
                // Display the window
                this->window->display();
                game.restart();

                break;
            case STATE::GAME_VS_FRIEND:
                game.eventHandler(*this, bestGame);
                // Clear the window
                this->window->clear(Colors::Background);

                // Draw the game
                game.draw();

                // Display the window
                this->window->display();


                break;
            case STATE::LOAD_GAME:
                loadGame.eventHandler(*this, game);

                this->window->clear(Colors::Background);

                // Draw the game
                loadGame.draw();

                // Display the window
                this->window->display();

                break;
            case STATE::BEST_GAME:
                bestGame.eventHandler(*this);
                // Clear the window
                this->window->clear(Colors::Background);

                // Draw the game
                bestGame.draw();

                // Display the window
                this->window->display();

                break;
        }
    }
}

void Controller::setState(STATE s){
    this->state = s;
}



