/********************************
*Filename:step1.cpp		*
*Login:by932			*								
*AssignmentNo:ass2		*
*DateLastModified:10/9/2014	*							
********************************/

#include <iostream>
#include <fstream>

using namespace std;

//	The following enumerated type indicates directions within the maze

enum Direction {DOWN, LEFT, UP, RIGHT};

//	The maze itself is indicated by # for the walls and an E for the end
//	All other locations in the maze can be any other character

typedef char Maze[17][17];

//	This struct is used for locations within the maze

struct Position
{
	int H, V;
};

//	These functions provide access to the maze
//	as well as provide manipulation of direction
//	of motion and maze location
//	See implementation for details

int LoadMaze(Maze,int&,int&,char[]);
void FindEntrance(Maze,Position&);
int AtExit(Maze,Position);
void ReportPosition(Maze,Position,int);
int Wall(Maze,Position);
void TurnRight(Direction&);
void MoveForward(int,Position&,Direction);
void WheresAhead(int,Position,Direction,Position&);
void TurnLeft(Direction&);
void WheresRight(int,Position,Direction,Position&);

int main()
{	
	Maze maze;
	Position pos, other;
	Direction heading;
	char fname[20];
	int mazeWidth, mazeHeight;
	cout << "Maze File: ";
	cin >> fname;
	if (LoadMaze(maze,mazeWidth,mazeHeight,fname))
	{
		FindEntrance(maze,pos);
		heading = DOWN;
		while (!AtExit(maze,pos))
		{
			ReportPosition(maze,pos,mazeWidth);
			WheresRight(mazeWidth,pos,heading,other);
			if (!Wall(maze,other))
			{
				TurnRight(heading);
				MoveForward(mazeWidth,pos,heading);
			}
			else
			{
				WheresAhead(mazeWidth,pos,heading,other);
				if (!Wall(maze,other))
					MoveForward(mazeWidth,pos,heading);
				else
					TurnLeft(heading);
			}
		}
		cout << "\nMaze solved" << endl;
	}
	return 0;
}
//	This function changes heading by turning left

void TurnLeft(Direction& heading)
{
	heading = Direction((int(heading)+3)%4);
}

//	This function takes a maze position and a heading and determines
//	the position to the right of this position
void WheresRight(int width, Position pos, Direction heading, Position& right)
{
	right = pos;
	switch (heading)
	{
		case DOWN:
			right.H--;
			break;
		case LEFT:
			right.V--;
			break;
		case UP:
			right.H++;
			break;
		case RIGHT:
			right.V++;
	}
}

//	This function loads the maze from the specified file
//	returning the maze and its dimensions
//	The height of the maze is not actually used anywhere but here

int	LoadMaze(Maze maze, int& width, int& height, char fname[])
{
	ifstream ifs(fname);
	
	if (ifs.good())
	{
		ifs >> width >> height;
		for (int i=0;i<height;i++)
			for (int j=0;j<width;j++)
				ifs >> maze[i][j];
		ifs.close();
		return 1;
	}
	else
	{
		cerr << "File not found." << endl;
		return 0;
	}
}

//	This function scans the maze array for the first non-wall item
//	It assumes that the entrance is in the top row of the maze array
	
void FindEntrance(Maze maze, Position& pos)
{
	pos.H = 0;
	pos.V = 0;
	
	while (Wall(maze,pos)) pos.H++;
}

//	This function returns TRUE if the maze position is the exit
//	identified by the character E

int AtExit(Maze maze, Position pos)
{
	return (maze[pos.V][pos.H] == 'E');
}

//	This function displays the position in the maze
//	At this time it specifies row and column of the array

void ReportPosition(Maze maze, Position pos, int width)
{
	cout << "Current position: (" << pos.V << ',' << pos.H << ')' << endl;
}


//	This function returns TRUE if maze position is wall

int Wall(Maze maze, Position pos)
{
	return (maze[pos.V][pos.H] == '#');
}

//	This function changes heading by turning right

void TurnRight(Direction& heading)
{
	heading = Direction((int(heading)+1)%4);
}

//	This function changes position in the maze by determining
//	the next position in the current direction

void MoveForward(int width, Position& pos, Direction heading)
{
	Position ahead;
	
	WheresAhead(width,pos,heading,ahead);
	pos = ahead;
}

//	This function determines the position in the direction
//	currently heading

void WheresAhead(int width, Position pos,
			Direction heading, Position& ahead)
{
	ahead = pos;
	switch (heading)
	{
		case DOWN:
			ahead.V++;
			break;
		case LEFT:
			ahead.H--;
			break;
		case UP:
			ahead.V--;
			break;
		case RIGHT:
			ahead.H++;
	}
}

