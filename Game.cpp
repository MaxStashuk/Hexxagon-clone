#include "Game.h"

Game::Game(sf::RenderWindow* window) {
    this->window = window;
    this->initFont();
    this->gameGrid = HexGrid();
    this->initButton();
    toMove = true; //true - Red moves , false - Blue moves
    this->clock.restart();
    this->clockTime = 0;
    this->baseTime = 0;
    this->paused = false;
}

void Game::initFont(){
    if(!this->font.loadFromFile("assets/consola.ttf")){
        std::cout<<"ERROR::Controller:: failed to init the font\n";
    }
}

void Game::initButton(){
    this->exitToMenu = Button(sf::Vector2f (300, 150), sf::Vector2f (30, 30), this->font, "Go to menu", 48);
}

void Game::nextMove(){
    toMove = !toMove;
}

void Game::eventHandler(Controller& c, BestGame& bestGame) {
    sf::Event event;
    while (this->window->pollEvent(event)) {
        //save the current state of grid
        if (event.type == sf::Event::Closed) {
            this->window->close();
        } else if (event.type == sf::Event::MouseButtonPressed){
            auto bufferedGrid = this->gameGrid;
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(*this->window);
                gameGrid.checkIfClicked(mousePosition, toMove);
                if(exitToMenu.isClickable(mousePosition)){
                    this->exitGame(c, bestGame);
                }
            }
            auto bufferedGridArray = bufferedGrid.gridToArray();
            auto gameGridArray = gameGrid.gridToArray();
            if(bufferedGridArray != gameGridArray){
                for(int i = 0; i < 9;i++){
                    for(int j = 0;j < 9;j++){
                        if(bufferedGridArray[i][j] == 'N' && (gameGridArray[i][j] == 'B' || gameGridArray[i][j] == 'R')){
                            gameGrid.eatNeighbors(std::make_pair(i, j));
                        }
                    }
                }
                this->nextMove();
            }
        } else if (event.type == sf::Event::MouseMoved) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(*this->window);
            this->exitToMenu.isClickable(mousePosition);
        }
    }
    if(!paused)
        this->clockTime = this->baseTime + this->clock.getElapsedTime().asSeconds();
}

void Game::exitGame(Controller& c, BestGame& bestGame){
    bestGame.updateScore(this->clockTime, gameGrid.gridToArray());
    c.setState(STATE::MENU);
    this->restart();
}

std::string Game::clockToStr(){
    //                 01234
    std::string res = "**:**";
    int seconds = this->clockTime;
    int secondsToWrite = seconds % 60;
    int minutes = seconds / 60;
    res[4] = (secondsToWrite % 10) + '0';
    res[3] = (secondsToWrite / 10) + '0';
    res[1] = (minutes % 10) + '0';
    res[0] = (minutes / 10) + '0';
    return res;
}

void Game::draw() {
    gameGrid.draw(this->window, this->font);
    exitToMenu.draw(this->window);

    //clock
    sf::Text clockText = sf::Text(this->clockToStr(), this->font);
    clockText.setFillColor(sf::Color::White);
    clockText.setCharacterSize(54);
    clockText.setPosition(sf::Vector2f(50, 900));
    this->window->draw(clockText);

    //pawn counter
    auto pawns = this->gameGrid.countPawns();
    int redPawns = pawns.x;
    int bluePawns = pawns.y;

    auto redCircle = sf::CircleShape(30);
    redCircle.setFillColor(Colors::RedPawn);
    redCircle.setPosition(1400, 800);

    std::string redTmp = "-  ";
    redTmp[1] = char(redPawns / 10)+'0';
    redTmp[2] = char(redPawns % 10)+'0';
    auto redNumber = sf::Text(redTmp, this->font);
    redNumber.setFillColor(Colors::Sign);
    redNumber.setCharacterSize(48);
    redNumber.setPosition(1475, 795);

    auto blueCircle = sf::CircleShape(30);
    blueCircle.setFillColor(Colors::BluePawn);
    blueCircle.setPosition(1400, 900);

    std::string blueTmp = "-  ";
    blueTmp[1] = char(bluePawns / 10)+'0';
    blueTmp[2] = char(bluePawns % 10)+'0';
    auto blueNumber = sf::Text(blueTmp, this->font);
    blueNumber.setFillColor(Colors::Sign);
    blueNumber.setCharacterSize(48);
    blueNumber.setPosition(1475, 895);

    this->window->draw(redCircle);
    this->window->draw(redNumber);
    this->window->draw(blueCircle);
    this->window->draw(blueNumber);

    if(this->isEnded()){
        auto pawnsAmount = gameGrid.countPawns();
        if(pawnsAmount.x > pawnsAmount.y){
            this->gameover("Red Won", Colors::RedPawn);
        } else if(pawnsAmount.y > pawnsAmount.x){
            this->gameover("Blue Won", Colors::BluePawn);
        }
    }
}

bool Game::isEnded(){
    std::vector<std::vector<std::pair<int, int>>> possibleMoves;
    for(int i = 0; i < 9;i++) {
        for(int j = 0; j < 9;j++) {
            if (this->toMove && this->gameGrid.gridToArray()[i][j] == 'R') {
                auto tmp = this->gameGrid.allPossibleMoves(std::make_pair(i, j));
                possibleMoves.push_back(tmp);
            } else if(!this->toMove && this->gameGrid.gridToArray()[i][j] == 'B'){
                auto tmp = this->gameGrid.allPossibleMoves(std::make_pair(i, j));
                possibleMoves.push_back(tmp);
            }
        }
    }
    auto pawnsAmount = gameGrid.countPawns();
    if (possibleMoves.empty()){
        return true;
    } else if (pawnsAmount.x == 0 || pawnsAmount.y == 0 || pawnsAmount.z == 0) {
        return true;
    } else {
        return false;
    }
}

void Game::gameover(std::string text, sf::Color c){
    this->paused = true;
    sf::Text winner = sf::Text(text, this->font);
    winner.setFillColor(Colors::Sign);
    winner.setCharacterSize(72);


    sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(800, 500));
    rect.setPosition(400, 250);
    rect.setFillColor(c);
    rect.setOutlineThickness(10);
    rect.setOutlineColor(Colors::Sign);

    auto textBounds = winner.getGlobalBounds();
    auto bodyBounds = rect.getGlobalBounds();
    winner.setPosition( (400 + bodyBounds.width / 2.f) - (textBounds.width / 2.f),
                            (250 + bodyBounds.height / 2.f) - textBounds.height);

    //bestGame.updateScore(this->clockTime, this->gameGrid.gridToArray());
    this->window->draw(rect);
    this->window->draw(winner);

    //1600x1000
}

void Game::restart(){
    this->gameGrid = HexGrid();
    toMove = true; //true - Red moves , false - Blue moves
    this->clock.restart();
    this->paused = false;
}

void Game::setMove(bool& move){
    this->toMove = move;
}

void Game::setClock(int& time){
    this->baseTime = time;
    this->paused = false;
}

void Game::setState(std::vector<std::vector<char>>& state){
    for(int i = 0;i < 9;i++){
        for(int j = 0;j < 9;j++){
            switch (state[i][j]) {
                case 'R':
                    this->gameGrid.setPawn(std::make_pair(i, j), PAWN::RED);
                    break;
                case 'B':
                    this->gameGrid.setPawn(std::make_pair(i, j), PAWN::BLUE);
                    break;
                case 'U':
                    this->gameGrid.setPawn(std::make_pair(i, j), PAWN::UNACTIVE);
                    break;
                case 'N':
                    this->gameGrid.setPawn(std::make_pair(i, j), PAWN::NONE);
                    break;
                default:
                    std::cerr<<"FAILED TO SET STATE TO A GAME\n";
                    return;
            }
        }
    }
}