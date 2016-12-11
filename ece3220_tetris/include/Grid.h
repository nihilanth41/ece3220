#ifndef __GRID_H
#define __GRID_H
#include <vector>
#include "Shapes.h"

using namespace std;

#define GRID_HEIGHT 20
#define GRID_WIDTH 10

class Grid { 
	public:
		vector<vector<int>> mGrid;
		Grid(); 
		void addShape(int type, int rotation, int x, int y);
		void moveShape(int type, int rotation, int x, int y);
		bool isMovementPossible(int type, int rotation, int x, int y);
		Shapes shapes;
};


#endif
