#ifndef __GAME_H
#define __GAME_H
#include "Grid.h"
#include "Shapes.h"
#include "Util.h"

class Game {
	public: 
		Game();
		Grid *g;
		// Main loop
		void Play(int speedVal);
		// Draw grid to screen
		void Draw();
		// Setup RNG, Init Random Shape
		void init_game();
		// Vars for shape
		int shapeType;
		int shapeRotation;
		// Coordinates for shape
		int sX, sY;
		void mainMenu();
		void settings();
		//user selection from main menu
		int menuSelection;
		//user selection from settings
		int settingsSelection;
		//Stores score value
		int currentScore;
		
		vector<int> highScores;
		//compare score to high scores after game is quit
		void loadScores();
		//reset high scores
		void clearScores();		
		// For keyboard echo in terminal
		void disableEcho();
		void restoreEcho();
		int speed;
		void printScores();
	private:
		// For disabling keyboard echo
		struct termios old_term, new_term;
		int nread;
		//opens high scores file if it exists
		void getScores();

		void saveScore(int);
				
};


#endif
