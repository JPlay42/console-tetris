#pragma once
#ifndef _GUI_H_
#define _GUI_H_

#include <ncurses.h>
#include "GameField.h"

class ActiveShape;
class GameField;

class Gui {
	int screen_size_x,
		screen_size_y,
	    frame_size_x,
	    frame_size_y,
	    frame_x,
	    frame_y;
	WINDOW* frame;
    GameField* gameField;
    ActiveShape* activeShape;

public:
	Gui(GameField* gameField);
	WINDOW* getWin();
	void init();	
	void updateScreen();
	void updateFrame();
	void paint(int x, int y, int color);
	void fillCell(int x, int y);
	void eraseActiveShape();
    void setActiveShape(ActiveShape* activeShape);
    void drawGameField();
    void drawActiveShape();
    void moveActiveShapeLeft();
    void moveActiveShapeRight();
    void moveActiveShapeDown();
    void rotateActiveShape();
};

#endif
