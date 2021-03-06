#include "GameField.h"
#include "ActiveShape.h"

GameField::GameField(int gf_size_x, int gf_size_y)
{
    this->gf_size_x = gf_size_x;
    this->gf_size_y = gf_size_y;
    try
    {
        field = new int *[gf_size_y];
    }
    catch (std::bad_alloc &xa)
    {
        std::cerr << "Allocation failure.\n";
        exit(1);
    }
    for (int i = 0; i < gf_size_y; i++)
        field[i] = new int[gf_size_x]{0};
}

GameField::~GameField()
{
    for (int i = 0; i < gf_size_y; i++)
    {
        delete[] field[i];
    }
}
int GameField::getSizeX()
{
    return gf_size_x;
}

int GameField::getSizeY()
{
    return gf_size_y;
}
int GameField::getCellValue(int x, int y)
{
    return field[y][x];
}

void GameField::mergeActiveShape(ActiveShape* shape) {
    for (int in_y = 0; in_y < 4; in_y++) {
        for(int in_x = 0; in_x < 4; in_x++) {
            if (shape->getCurrentState()->getValue(in_x, in_y)) {
                field[shape->getY() + in_y][shape->getX() + in_x] = shape->getColor();
            }
        }
    }
}

bool GameField::isGameOver() {
    for(int x = 0; x < gf_size_x; x++) {
        if(getCellValue(x, 0)) {
            return true;
        }
    }
    return false;
}

bool GameField::isGameWon() {
    for(int y = 1; y < gf_size_y; y++) {
        bool isGameWon = true;
        for(int x = 0; x < gf_size_x; x++)
            if(!getCellValue(x, y))
                isGameWon = false;
        if (isGameWon)
            return true;
    }
    return false;
}

