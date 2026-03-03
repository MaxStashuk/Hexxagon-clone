#include "BestGame.h"

BestGame::BestGame(sf::RenderWindow* window) {
    this->window = window;
    this->initFont();
    this->goToMenu = Button(sf::Vector2f (300, 150), sf::Vector2f (30, 30), this->font, "Go to menu", 48);
    this->initScore();
}



void BestGame::initFont(){
    if(!this->font.loadFromFile("assets/consola.ttf")){
        std::cout<<"ERROR::Controller:: failed to init the font\n";
    }
}

void BestGame::initScore(){
    std::ifstream score("score.txt");
    if(!score){
        std::ofstream newScore("score.txt");
        newScore << "Fastest game\nN/A\nBiggest blowout\nN/A\nend\n";
        newScore.close();
    }
    score.close();
}

//red -> first, blue ->second
std::pair< int, int > BestGame::evaluateScore(std::vector<std::vector<char>> gridArray){
    int red = 0, blue = 0;
    for(int i = 0;i < 9;i++){
        for(int j = 0; j < 9; j++){
            if(gridArray[i][j] == 'R'){
                red++;
            } else if(gridArray[i][j] == 'B'){
                blue++;
            }
        }
    }
    return std::make_pair(red, blue);
}

std::pair<std::vector<int>, std::vector<int>> BestGame::getScore() {
    std::ifstream score("score.txt");

    std::string line;
    int r1 = 0, b1 = 0, t1 = INT_MAX, r2 = 0, b2 = 0, t2 = INT_MAX;
    int i = 0;

    if(score.is_open()) {
        while(std::getline(score, line)) {
            if(line == "Fastest game"){
                i++;
            } else if(line == "Biggest blowout"){
                i++;
            } else {
                std::istringstream tmpline(line);
                if(i == 1){
                    if(line == "N/A"){
                        continue;
                    } else {
                        tmpline >> r1 >> b1 >> t1;
                    }
                } else if(i == 2){
                    if(line == "N/A"){
                        continue;
                    } else {
                        tmpline >> r2 >> b2 >> t2;
                    }
                }
            }
        }
    }
    score.close();

    std::vector<int> v1 = {r1, b1, t1};
    std::vector<int> v2 = {r2, b2, t2};
    return std::make_pair(v1, v2);
}

void BestGame::updateScore(int time, std::vector<std::vector<char>> gridArray){
    auto scores = this->getScore();
    std::vector<int> fastest = scores.first;
    std::vector<int> biggestBlowout = scores.second;
    //r b t
    //0 1 2

    std::pair<int, int> curScore = this->evaluateScore(gridArray);

    bool newFastest = false;
    bool newBiggest = false;

    if(time < fastest[2]){
        fastest[0] = curScore.first;
        fastest[1] = curScore.second;
        fastest[2] = time;
        newFastest = true;
    }
    if(std::abs(biggestBlowout[0] - biggestBlowout[1]) < std::abs(curScore.first - curScore.second)){
        biggestBlowout[0] = curScore.first;
        biggestBlowout[1] = curScore.second;
        biggestBlowout[2] = time;
        newBiggest = true;
    }
    std::ofstream newScore("score.txt");
    if(newFastest){
        newScore << "Fastest game\n";
        newScore << fastest[0] << ' ' << fastest[1] << ' ' << fastest[2] << '\n';
    } else {
        if(fastest[0] == 0 && fastest[1] == 0 && fastest[2] == INT_MAX){
            newScore<<"Fastest game\nN/A\n";
        } else {
            newScore << "Fastest game\n";
            newScore << fastest[0] << ' ' << fastest[1] << ' ' << fastest[2] << '\n';
        }
    }
    if(newBiggest){
        newScore << "Biggest blowout\n";
        newScore << biggestBlowout[0] << ' ' << biggestBlowout[1] << ' ' << biggestBlowout[2] << '\n';
    } else {
        if(biggestBlowout[0] == 0 && biggestBlowout[1] == 0 && biggestBlowout[2] == INT_MAX){
            newScore << "Biggest blowout\nN/A\n";
        } else {
            newScore << "Biggest blowout\n";
            newScore << biggestBlowout[0] << ' ' << biggestBlowout[1] << ' ' << biggestBlowout[2] << '\n';
        }
    }
    newScore.close();
}

void BestGame::eventHandler(Controller& c){
    sf::Event event;
    while(this->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->window->close();
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(*this->window);
                if(goToMenu.isClickable(mousePosition)){
                    this->exitBestGame(c);
                }
            }
        } else if (event.type == sf::Event::MouseMoved) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(*this->window);
            this->goToMenu.isClickable(mousePosition);
        }
    }
}

void BestGame::exitBestGame(Controller& c){
    c.setState(STATE::MENU);
}

std::string BestGame::timeToStr(int seconds){
    //                 01234
    std::string res = "**:**";
    int secondsToWrite = seconds % 60;
    int minutes = seconds / 60;
    res[4] = (secondsToWrite % 10) + '0';
    res[3] = (secondsToWrite / 10) + '0';
    res[1] = (minutes % 10) + '0';
    res[0] = (minutes / 10) + '0';
    return res;
}

void BestGame::draw(){
    //init two labels:
    sf::RectangleShape fastestGameLabel = sf::RectangleShape(sf::Vector2f(800, 200));
    fastestGameLabel.setPosition(sf::Vector2f(400, 200));
    fastestGameLabel.setFillColor(Colors::ButtonBody);

    sf::RectangleShape biggestBlowout = sf::RectangleShape(sf::Vector2f(800, 200));
    biggestBlowout.setPosition(sf::Vector2f(400, 600));
    biggestBlowout.setFillColor(Colors::ButtonBody);

    //initializing the signs
    sf::Text fastestGameSign;
    fastestGameSign = sf::Text("Fastest Game", font);
    fastestGameSign.setCharacterSize(68);
    fastestGameSign.setFillColor(Colors::Sign);

    sf::Text blowoutSign;
    blowoutSign = sf::Text("Biggest Blowout", font);
    blowoutSign.setCharacterSize(68);
    blowoutSign.setFillColor(Colors::Sign);

    //putting the sign above the label
    auto textBounds = fastestGameSign.getGlobalBounds();
    auto bodyBounds = fastestGameLabel.getGlobalBounds();
    fastestGameSign.setPosition((400 + bodyBounds.width / 2.f) - (textBounds.width / 2.f),
                            (bodyBounds.height / 2.f) - textBounds.height / 2.f);


    auto textBounds1 = blowoutSign.getGlobalBounds();
    auto bodyBounds1 = biggestBlowout.getGlobalBounds();
    blowoutSign.setPosition((400 + bodyBounds1.width / 2.f) - (textBounds1.width / 2.f),
                                (400 + bodyBounds1.height / 2.f) - textBounds1.height / 2.f);

    auto fastestGameScore = this->getScore().first;
    std::string fastestScoreStr = "";

    if(fastestGameScore[0] == 0 && fastestGameScore[1] == 0 && fastestGameScore[2] == INT_MAX){
        fastestScoreStr = "No games played";
    } else {
        fastestScoreStr += "Red: " + std::to_string(fastestGameScore[0]) + "; ";
        fastestScoreStr += "Blue: " + std::to_string(fastestGameScore[1]) + "; ";
        fastestScoreStr += "Time: " + this->timeToStr(fastestGameScore[2]);
    }

    sf::Text fastestScoreText = sf::Text(fastestScoreStr, this->font);
    fastestScoreText.setCharacterSize(48);
    fastestScoreText.setFillColor(sf::Color::White);
    auto scoreTextBounds = fastestScoreText.getGlobalBounds();
    fastestScoreText.setPosition((400 + bodyBounds.width / 2.f) - (scoreTextBounds.width / 2.f),
                                200 + (bodyBounds.height / 2.f) - scoreTextBounds.height / 2.f);


    auto blowoutScore = this->getScore().second;
    std::string blowoutStr = "";

    if(blowoutScore[0] == 0 && blowoutScore[1] == 0 &&blowoutScore[2] == INT_MAX){
        blowoutStr = "No games played";
    } else {
        blowoutStr += "Red: " + std::to_string(blowoutScore[0]) + "; ";
        blowoutStr += "Blue: " + std::to_string(blowoutScore[1]) + "; ";
        blowoutStr += "Time: " + this->timeToStr(blowoutScore[2]);
    }

    sf::Text blowoutText = sf::Text(blowoutStr, this->font);
    blowoutText.setCharacterSize(48);
    blowoutText.setFillColor(sf::Color::White);
    auto scoreTextBounds1 = blowoutText.getGlobalBounds();
    blowoutText.setPosition((400 + bodyBounds1.width / 2.f) - (scoreTextBounds1.width / 2.f),
                                 600 + (bodyBounds1.height / 2.f) - scoreTextBounds1.height / 2.f);


    this->goToMenu.draw(this->window);

    this->window->draw(fastestGameLabel);
    this->window->draw(fastestGameSign);
    this->window->draw(fastestScoreText);

    this->window->draw(biggestBlowout);
    this->window->draw(blowoutSign);
    this->window->draw(blowoutText);
}