#include <ncurses.h>
#include <cstdlib>
#include <iostream>
#include "Gui.h"

Gui::Gui(int gf_size_x, int gf_size_y) {
	frame_size_x = 2*gf_size_x;
	frame_size_y = gf_size_y;
}

void Gui::init() {
	initscr();
	cbreak();

	if (!has_colors()) {
		endwin();
		std::cout << "The terminal does not support colors" << std::endl;
	}
	start_color();
    init_pair(1, COLOR_BLACK, COLOR_RED);
	init_pair(2, COLOR_BLACK, COLOR_YELLOW);
	init_pair(3, COLOR_BLACK, COLOR_GREEN);
	init_pair(4, COLOR_BLACK, COLOR_CYAN);
	init_pair(5, COLOR_BLACK, COLOR_BLUE);
	init_pair(6, COLOR_BLACK, COLOR_MAGENTA);   

	frame = newwin(frame_size_y + 2, frame_size_x + 2, 0, 0);

	updateScreen();

}

void Gui::updateScreen() {
	clear();
	getmaxyx(stdscr, screen_size_y, screen_size_x);
	frame_y = (screen_size_y - frame_size_y) / 2 - 1;
	frame_x = (screen_size_x - frame_size_x) / 2 - 1;

	if (frame_x <= 0 || frame_y <= 0){
    	endwin();
    	std::cout << "Terminal window is too small" << std::endl;
    	exit(1);
    }

    mvwin(frame, frame_y, frame_x);
	box(frame, 0, 0);

    refresh();
    move(0, 0);
    updateFrame();
}

void Gui::updateFrame() {
    wrefresh(frame);
    move(0, 0);
}

void Gui::paint(int x, int y, int color) {
	switch(color) {
		case 0:
		fillCell(x, y);
		break;
		default:
		wattron(frame, COLOR_PAIR(color));
		fillCell(x, y);
		wattroff(frame, COLOR_PAIR(color));
	}
}

void Gui::fillCell(int x, int y) {
	mvwaddch(frame, y + 1, 2*x + 1, ' ');
	mvwaddch(frame, y + 1, 2*x + 2, ' ');
}