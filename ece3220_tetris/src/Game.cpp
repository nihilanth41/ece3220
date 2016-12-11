#include "Game.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include "Colors.h"
using namespace std;

Game::Game() {
	currentScore = 0;
	loadScores();
	speed = 100000;
}


void Game::init_game(void) { 
	// Setup RNG
	srand(time(NULL));
	// Get random shape
	shapeType = rand() % 7;
	// Get random rotation
	shapeRotation = rand() % 4;
	// Set initial position of shape
	sX = 4;
	sY = 14;

}

void Game::Draw(void) {
	cout << "\r";
	cout<<"Score: "<< currentScore << endl;
	for(int j=20; j--;)
	{
		cout << "[";
		for(int i=0; i<10; i++)
		{
			char buf[64];
			if(g->mGrid[i][j] == 1){
				sprintf(buf, "%s %d %s", ANSI_COLOR_YELLOW, g->mGrid[i][j], ANSI_COLOR_RESET);
				cout<<buf;
			}
			else if(g->mGrid[i][j] == 2){
				sprintf(buf, "%s %d %s", ANSI_COLOR_CYAN, g->mGrid[i][j], ANSI_COLOR_RESET);
				cout<<buf;
			}
			else if(g->mGrid[i][j] == 3){
				sprintf(buf, "%s %d %s", ANSI_COLOR_WHITE, g->mGrid[i][j], ANSI_COLOR_RESET);
				cout<<buf;
			}
			else if(g->mGrid[i][j] == 4){
				sprintf(buf, "%s %d %s",ANSI_COLOR_BLUE, g->mGrid[i][j], ANSI_COLOR_RESET);
				cout<<buf;
			}
			else if(g->mGrid[i][j] == 5){
				sprintf(buf, "%s %d %s", ANSI_COLOR_RED, g->mGrid[i][j], ANSI_COLOR_RESET);
				cout<<buf;
			}
			else if(g->mGrid[i][j] == 6){
				sprintf(buf, "%s %d %s", ANSI_COLOR_GREEN, g->mGrid[i][j], ANSI_COLOR_RESET);
				cout<<buf;
			}	
			else if(g->mGrid[i][j] == 7){
				sprintf(buf, "%s %d %s", ANSI_COLOR_MAGENTA, g->mGrid[i][j], ANSI_COLOR_RESET);
				cout<<buf;
			}
			else if(g->mGrid[i][j] == 0){
				cout << "   "; 
			}
		}
		cout << "]" << endl;
	}
	printf("\033[21A");
}

void Game::mainMenu() {
	cout<<"Main Menu"<<endl<<"Select one of the following:"<<endl;
	cout<<"1 Play Game"<<endl;
	cout<<"2 High Score"<<endl;
	cout<<"3 Settings"<<endl;
	cout<<"4 Quit"<<endl;
}

void Game::disableEcho(void) {
	/* Turn echoing off and fail silently if we can’t. */
	tcgetattr(fileno (stdin), &old_term);
	new_term = old_term;
	new_term.c_lflag &= ~ECHO;
	tcsetattr (fileno (stdin), TCSAFLUSH, &new_term);
}

void Game::restoreEcho(void) {
	// Restore terminal
	(void) tcsetattr (fileno (stdin), TCSAFLUSH, &old_term);
}

void Game::Play(int speedVal) {

speed = speedVal;

while(1) {
	// Get random shape
	init_game();
	
	// Initialize a Grid
	// Add the shape to the Grid
	Grid grid;
	grid.addShape(shapeType, shapeRotation, sX, sY);

	// Give game a grid to work with
	g = &grid;

	// Disable keyboard echo
	//disableEcho();
	while(sY > 1)
	{
		// Draw screen
		Draw();
		// Decrement y value (if possible)
		sY -= 1;
		// Need some kind of isMovementPossible(), maybe inside the MoveShape() method.
		// Translate shape according to user input and/or sleep.
		for(int i=0; i<5; i++)
		{
			grid.moveShape(shapeType, shapeRotation, sX, sY);
			if( _kbhit() )
			{
				// Get user input
				char c;  
				scanf(" %c" , &c);
				switch(c)
				{
					case 'j': {
							  //left
							  if(grid.isMovementPossible(shapeType, shapeRotation, sX-1, sY)) { 
							  // maybe instead of clearing the old position we just clear the entire grid and redraw?
							  	sX -= 1;
							  	grid.moveShape(shapeType, shapeRotation, sX, sY);
							  	Draw();
							  }
							  break;
						  }
					case 'k': {
							  //right
							  if(grid.isMovementPossible(shapeType, shapeRotation, sX+1, sY)) { 
								sX += 1;
								grid.moveShape(shapeType, shapeRotation, sX, sY);
								Draw();
							  }
							  break;
						  }
					case 'l': {
							  int newRotation;
							  if(shapeRotation == 3)
							  {
								  newRotation = 0;
							
							  } 
							  else {
								  newRotation = shapeRotation+1;
							  }
							  //rotate
							  if(grid.isMovementPossible(shapeType, newRotation, sX, sY)) { 
								shapeRotation = newRotation;
								grid.moveShape(shapeType, shapeRotation, sX, sY);
								Draw();
							  }
							  break;
						  }
					case 'q':
					case 'Q': {
							  // Clear screen
							  // From http://stackoverflow.com/a/7660837
							  printf("\e[1;1H\e[2J");	
							  // Save to file if high score
							  saveScore(currentScore);
							  printScores();
							  // Restore terminal
							  //restoreEcho();
							  exit(0);
						  }
					default: break;
				}
			}
			// 200ms * 5 = 1 sec
			usleep(speed);
			currentScore++;	
		}
			
	}
	//restoreEcho();
	} 
}


void Game::loadScores(){
	int temp;	
	FILE* fp = fopen("HighScores.txt", "r");
		if(fp == NULL){
			cout<<"Error viewing highscores"<<endl;
			exit(-1);
		}
		
		for(int i = 0; i<5; i++){
			fscanf(fp, "%d", &temp);
			highScores.push_back(temp);
		}
		fclose(fp);

}

void Game::printScores(void) {
	cout << "\n -- High Scores --" << endl;
	cout << "Position Score" << endl;
	for(int i=0; i<5; i++)
	{	
		cout << i+1 << "\t " << highScores[i] << endl;
	}
}

void Game::saveScore(int score) {
	// Check if score is > any of the top five scores and save if true
	// Check highest first
	for(int i=0; i<5; i++)
	{	
		if(score > highScores[i])		
		{ 
			cout << "New high score!" << endl;
			cout << "Position: " << i+1 << endl;
			cout << "Score: " << currentScore << endl;
			highScores[i] = score;
			// Overwrite file 
			FILE *fp_w = fopen("HighScores.txt", "w");
			if(fp_w != NULL)
			{
				for(int j=0; j<5; j++)
				{	
					fprintf(fp_w, "%d\n", highScores[j]);
				}
				fclose(fp_w); } break; } }
}
			
void Game::settings() {
	cout<<"Settings"<<endl<<"Select one of the following:"<<endl;
	cout<<"1 Clear High Scores"<<endl;
	cout<<"2 Increase Speed"<<endl;
	cout<<"3 Decrease Speed"<<endl;
	cout<<"4 Default Speed"<<endl;
	cout<<"5 Back"<<endl;
	cout<<"6 Quit"<<endl;
}

void Game::clearScores(){

	for(int i=0; i<5; i++)
	{	
		
			highScores[i] = 0;
			// Overwrite file 
			FILE *fp_w = fopen("HighScores.txt", "w");
			if(fp_w != NULL)
			{
				for(int j=0; j<5; j++)
				{	
					fprintf(fp_w, "%d\n", highScores[j]);
				}
			 fclose(fp_w); 
			}  
	} 

}


