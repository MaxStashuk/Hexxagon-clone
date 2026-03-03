#include "LoadGame.h"

LoadGame::LoadGame(sf::RenderWindow* window) {
    this->window = window;
    this->initFont();
    this->goToMenu = Button(sf::Vector2f (300, 150), sf::Vector2f (30, 30), this->font, "Go to menu", 48);
    this->startGame = Button(sf::Vector2f(400, 150), sf::Vector2f (600,500), this->font, "Load game", 54);
    this->input = "";
    this->textBox = TextBox(sf::Vector2f(1000, 150), sf::Vector2f(300, 300), input, this->font, 56);

}

void LoadGame::initFont() {
    if(!this->font.loadFromFile("assets/consola.ttf")){
        std::cout<<"ERROR::Controller:: failed to init the font\n";
    }
}

void LoadGame::eventHandler(Controller& c, Game& game){
    sf::Event event;
    std::string tmp = this->input;
    while(this->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->window->close();
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(*this->window);
                if(goToMenu.isClickable(mousePosition)){
                    this->exitLoadGame(c);
                } else if(startGame.isClickable(mousePosition)){
                    if(!this->isSaveExists(textBox.getString())){
                        std::cerr<<"There's no such a file with specified path\n";
                    } else {
                        std::cout<<"Parsing^_^\n";
                        auto data = this->parseFile(textBox.getString());
                        if(data.second.second == std::vector<std::vector < char > > (1, std::vector<char> ('X'))){
                            std::cout<<"Couldn't init the game state. Wrong data\n";
                        } else {
                            std::cout<<"Initializing game from file\n";
                            game.setMove(data.first);
                            game.setClock(data.second.first);
                            game.setState(data.second.second);
                            c.setState(STATE::GAME_VS_FRIEND);
                            std::cout<<"Changed state\n";
                        }
                    }
                }
            }
        } else if(event.type == sf::Event::TextEntered){
            if(event.text.unicode == '\b'){
                if(input.size()){
                    input.erase(input.size() - 1);
                }
            } else if (event.text.unicode < 128) {
                this->input += static_cast<char>(event.text.unicode);
            }
        } else if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(*this->window);
                this->goToMenu.isClickable(mousePosition);
                this->startGame.isClickable(mousePosition);
        }
    }
    this->textBox.setString(input);
}

void LoadGame::exitLoadGame(Controller& c){
    c.setState(STATE::MENU);
}

bool LoadGame::isSaveExists(std::string savePath){
    std::ifstream saveFile(savePath);
    if(!saveFile){
        return false;
    }
    return true;
}

void LoadGame::draw(){
    this->goToMenu.draw(this->window);
    this->textBox.draw(this->window);
    this->startGame.draw(this->window);
}


std::pair<bool, std::pair <int, std::vector<std::vector<char>>>> LoadGame::parseFile(std::string fileName){
    std::fstream stateFile(fileName);
    std::string line;
    std::vector <std::vector < char > >  matrix(9, std::vector<char> (9));
    bool move;
    int clockTime;
    auto gridToCompare= HexGrid().gridToArray();
    int i = 0;
    if(stateFile.is_open()) {
        while(std::getline(stateFile, line)){
            std::vector <char> fileToVector;
            std::istringstream lineToParse(line);

            if(i == 0){
                if(line == "true"){
                    move = true;
                } else {
                    move = false;
                }
            } else if(i == 1) {
                clockTime = std::stoi(line);
            } else {
                for (int j = 0; j < 9; j++) {
                    char tmp;
                    lineToParse >> tmp;
                    if ((gridToCompare[i-2][j] == 'U' && tmp != 'U') ||
                        (gridToCompare[i-2][j] != 'U' && tmp == 'U')) {
                        std::cerr << "File is broken. State loading is unpossible. Illegal state\n";
                        return std::make_pair(-1, std::make_pair(-1, std::vector<std::vector<char>>{{'X'}}));
                    }
                    matrix[i - 2][j] = tmp;
                }
            }
            i++;
        }
    }
    stateFile.close();
    for(auto matrixLine : matrix){
        fmt::println("{}", matrixLine);
    }
    if(i != 11){
        std::cerr << "File is broken. State loading is unpossible. Too little lines\n";
        return std::make_pair(-1, std::make_pair(-1, std::vector<std::vector<char>>{{'X'}}));
    } else {
        return std::make_pair(move, std::make_pair(clockTime, matrix));
    }
}


