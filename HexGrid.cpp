#include "HexGrid.h"
#include <iostream>
#include <fmt/ranges.h>

class Game;

HexGrid::HexGrid() : selectedHex(-1, -1) {
    //std::cout<<"Created new grid";
    for(int i = 0;i < 9;i++) {
        for(int j = 0;j < 9;j++){
            grid[i][j].setCoords(i, j);
        }
    }

    //top corners
    grid[0][0].setPawn(PAWN::UNACTIVE);
    grid[0][1].setPawn(PAWN::UNACTIVE);
    grid[1][0].setPawn(PAWN::UNACTIVE);
    grid[2][0].setPawn(PAWN::UNACTIVE);
    grid[6][0].setPawn(PAWN::UNACTIVE);
    grid[7][0].setPawn(PAWN::UNACTIVE);
    grid[8][0].setPawn(PAWN::UNACTIVE);
    grid[8][1].setPawn(PAWN::UNACTIVE);

    //bottom corners
    grid[0][7].setPawn(PAWN::UNACTIVE);
    grid[0][8].setPawn(PAWN::UNACTIVE);
    grid[1][7].setPawn(PAWN::UNACTIVE);
    grid[2][8].setPawn(PAWN::UNACTIVE);
    grid[6][8].setPawn(PAWN::UNACTIVE);
    grid[7][7].setPawn(PAWN::UNACTIVE);
    grid[8][7].setPawn(PAWN::UNACTIVE);
    grid[8][8].setPawn(PAWN::UNACTIVE);
    grid[8][1].setPawn(PAWN::UNACTIVE);
    grid[8][7].setPawn(PAWN::UNACTIVE);
    grid[1][8].setPawn(PAWN::UNACTIVE);
    grid[3][8].setPawn(PAWN::UNACTIVE);
    grid[5][8].setPawn(PAWN::UNACTIVE);
    grid[7][8].setPawn(PAWN::UNACTIVE);


    //middle cells
    grid[4][3].setPawn(PAWN::UNACTIVE);
    grid[3][4].setPawn(PAWN::UNACTIVE);
    grid[5][4].setPawn(PAWN::UNACTIVE);

    //red team pawns
    grid[4][0].setPawn(PAWN::RED);
    grid[8][6].setPawn(PAWN::RED);
    grid[0][6].setPawn(PAWN::RED);

    //blue team pawns
    grid[0][2].setPawn(PAWN::BLUE);
    grid[8][2].setPawn(PAWN::BLUE);
    grid[4][8].setPawn(PAWN::BLUE);
    this->setPos();
}

HexGrid::HexGrid(std::vector<std::vector<char>> state) : selectedHex(-1, -1) {
    for(int i = 0;i < 9;i++) {
        for(int j = 0;j < 9;j++){
            grid[i][j].setCoords(i, j);
        }
    }

    for(int i = 0; i < 9;i++){
        for(int j = 0; j < 9; j++) {
            switch(state[i][j]){
                case 'R':
                    grid[i][j].setPawn(PAWN::RED);
                    break;
                case 'B':
                    grid[i][j].setPawn(PAWN::BLUE);
                    break;
                case 'U':
                    grid[i][j].setPawn(PAWN::UNACTIVE);
                    break;
                case 'N':
                    grid[i][j].setPawn(PAWN::NONE);
                    break;
            }
        }
    }

    this->setPos();
}

void HexGrid::setPos() {
    for(int i = 0;i < 9;i++){
        for(int j = 0; j < 9; j++){
            grid[i][j].setPosition(grid[i][j].coordsToPos());
        }
    }
}

std::string HexGrid::tmp(int i, int j){
    std::string res = "";
    res += std::to_string(i) + " " + std::to_string(j);
    return res;
}

void HexGrid::draw(sf::RenderWindow* window, sf::Font font) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j].getPawn() != PAWN::UNACTIVE) {
                if (selectedHex == std::make_pair(i, j)) {
                    grid[i][j].update(sf::Color::Cyan);
                }
                else if(std::count(oneDistance.begin(), oneDistance.end(), std::make_pair(i, j))){
                    grid[i][j].update(sf::Color::Green);
                }
                else if(std::count(twoDistance.begin(), twoDistance.end(), std::make_pair(i, j))){
                    grid[i][j].update(sf::Color::Yellow);
                }

                grid[i][j].draw(window);
                /*std::string result = tmp(i, j);
                sf::Text text(result, font);
                text.setFillColor(Colors::Sign);
                text.setCharacterSize(18);
                auto bounds = text.getLocalBounds();
                text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
                text.setPosition(grid[i][j].getPosition());
                window->draw(text);*/
            }
        }
    }
}

void HexGrid::checkIfClicked(sf::Vector2i& mousePos, bool toMove) {
    if (selectedHex.first != -1 && selectedHex.second != -1) {
        grid[selectedHex.first][selectedHex.second].setDefaultOutline();
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j].isClickable(mousePos, toMove)) {
                selectedHex = {i, j};
                this->select();
                return;
            } else if (grid[i][j].isClickable(mousePos) && selectedHex != std::make_pair(-1, -1)) {
                if (std::count(oneDistance.begin(), oneDistance.end(), std::make_pair(i, j))
                    || std::count(twoDistance.begin(), twoDistance.end(), std::make_pair(i, j))) {
                    /*fmt::println("one dist: {}", oneDistance);
                    fmt::println("two dist: {}", twoDistance);*/
                    moveHex(grid[selectedHex.first][selectedHex.second], grid[i][j]);
                }
                return;
            }
        }
    }
    //unselect();
    selectedHex = {-1, -1};
}

void HexGrid::select(){
    unselect();
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j].getPawn() == PAWN::NONE) {
                if (grid[i][j].distance(grid[selectedHex.first][selectedHex.second]) == 1) {
                    oneDistance.push_back(std::make_pair(i, j));
                } else if (grid[i][j].distance(grid[selectedHex.first][selectedHex.second]) == 2) {
                    twoDistance.push_back(std::make_pair(i, j));
                }
            }
        }
    }
}

std::vector<std::pair <int, int>> HexGrid::allPossibleMoves(std::pair<int, int> hex){
    int x = hex.first;
    int y = hex.second;
    std::vector<std::pair <int, int>> res;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j].getPawn() == PAWN::NONE) {
                if (grid[i][j].distance(grid[x][y]) == 1 ||grid[i][j].distance(grid[x][y]) == 2) {
                    res.push_back(std::make_pair(i, j));
                }
            }
        }
    }
    return res;
}

void HexGrid::setPawn(std::pair<int, int> hex, PAWN p){
    this->grid[hex.first][hex.second].setPawn(p);
}



void HexGrid::unselect(){
    if(selectedHex != std::make_pair(-1, -1)) {
        grid[selectedHex.first][selectedHex.second].setDefaultOutline();
    }
    //selectedHex = std::make_pair(0, 0);

    for(std::pair<int, int> p : oneDistance){
        grid[p.first][p.second].setDefaultOutline();
    }
    for(std::pair<int, int> p : twoDistance){
        grid[p.first][p.second].setDefaultOutline();
    }
    oneDistance.clear();
    twoDistance.clear();
}

void HexGrid::moveHex(Hex selected, Hex moveTo){
    auto moveToCoords = moveTo.getCoords();
    auto selectedCoords= selected.getCoords();
    if(selected.distance(moveTo) == 1){
        grid[moveToCoords.first][moveToCoords.second].setPawn(selected.getPawn());
    } else if (selected.distance(moveTo) == 2){
        grid[moveToCoords.first][moveToCoords.second].setPawn(selected.getPawn());
        grid[selectedCoords.first][selectedCoords.second].setPawn(PAWN::NONE);
    }
    unselect();
}

std::vector<std::vector<char>> HexGrid::gridToArray(){
    std::vector<std::vector<char>> res(9, std::vector<char> (9));
    for(int i = 0;i < 9;i++){
        for(int j = 0;j < 9;j++){
            switch(grid[i][j].getPawn()){
                case PAWN::UNACTIVE:
                    res[i][j] = 'U';
                    break;
                case PAWN::RED:
                    res[i][j] = 'R';
                    break;
                case PAWN::BLUE:
                    res[i][j] = 'B';
                    break;
                case PAWN::NONE:
                    res[i][j] = 'N';
                    break;
            }
        }
    }
    return res;
}

void HexGrid::eatNeighbors(std::pair<int, int> hexCoords){
    //zahavat' sosedov
    std::vector < std::vector < std::pair <int, int >>> directions = {
            {{0, -1}, {1, -1}, {1, 0},
                    {0, 1}, {-1, 0}, {-1, -1}},
            {{0, -1}, {1, 0}, {1, 1},
                    {0, 1}, {-1, 1}, {-1, 0}}
    };
    int parity = hexCoords.first & 1;
    for(int i = 0; i < 6;i++){
        if(isEatable(hexCoords, directions[parity][i])){
            grid[hexCoords.first + directions[parity][i].first][hexCoords.second + directions[parity][i].second].setPawn(grid[hexCoords.first][hexCoords.second].getPawn());
        }
    }
}

bool HexGrid::isEatable(std::pair<int, int> hex, std::pair <int, int> direction){
    int x = hex.first + direction.first;
    int y = hex.second + direction.second;
    auto colorMatch = [](PAWN p1, PAWN p2) -> bool{
        if(p1 == PAWN::RED && p2 == PAWN::BLUE){
            return true;
        } else if(p1 == PAWN::BLUE && p2 == PAWN::RED){
            return true;
        } else {
            return false;
        }
    };
    if ((x >= 0) && (x <= 9) && (y >= 0) && (y <= 9)) {
        return colorMatch(grid[hex.first][hex.second].getPawn(), grid[x][y].getPawn());
    } else {
        return false;
    }
}

sf::Vector3i HexGrid::countPawns(){
    sf::Vector3i res = sf::Vector3i(0, 0, 0);
    //x - Red, y - Blue, z - None
    for(int i = 0;i < 9;i++){
        for(int j = 0;j < 9;j++){
            switch(grid[i][j].getPawn()){
                case PAWN::RED:
                    res.x++;
                    break;
                case PAWN::BLUE:
                    res.y++;
                    break;
                case PAWN::NONE:
                    res.z++;
                    break;
                default:
                    break;
            }
        }
    }
    return res;
}