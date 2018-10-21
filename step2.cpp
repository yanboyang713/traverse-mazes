/********************************
*Filename:step2.cpp		*
*Login:by932			*								
*AssignmentNo:ass2		*
*DateLastModified:11/9/2014	*							
********************************/

#include <iostream>
#include <fstream>
//#include <cstring>

using namespace std;

//	The following enumerated type indicates directions within the maze

enum Direction {DOWN, LEFT, UP, RIGHT};

//	The maze itself is indicated by # for the walls and an E for the end
//	All other locations in the maze can be any other character

typedef char Maze[400];


//	These functions provide access to the maze
//	as well as provide manipulation of direction
//	of motion and maze location
//	See implementation for details

int LoadMaze(Maze,int&,int&,char[]);
void FindEntrance(Maze,int&);
int AtExit(Maze, int);
void ReportPosition(Maze, int,int);
int Wall(Maze, int);
void TurnRight(Direction&);
int MoveForward(int, int&,Direction);
void WheresAhead(int, int,Direction, int&);
void TurnLeft(Direction&);
void WheresRight(int, int,Direction, int&);

int main()
{	
	Maze maze = {'\0'};
	int pos = 0;
	int other = 0;
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
				other = MoveForward(mazeWidth,pos,heading);
				if (maze[other] != '#')
				{
					pos = other;
				}

			}
			else
			{
						
				WheresAhead(mazeWidth,pos,heading,other);
				if (!Wall(maze,other))
				{
					other = MoveForward(mazeWidth,pos,heading);
					if (maze[other] != '#')
					{
						pos = other;
					}
				}
				else
				{
					TurnLeft(heading);
					other = MoveForward(mazeWidth,pos,heading);
					if (maze[other] != '#')
					{
						pos = other;
					}
					
				}
				
					
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
void WheresRight(int width, int pos, Direction heading, int& right)
{
	right = pos;
	
	switch (heading)
	{
		case DOWN:
			right--;
			break;
		case LEFT:
			right -= width;
			break;
		case UP:
			right++;
			break;
		case RIGHT:
			right += width;
	}
}

//	This function loads the maze from the specified file
//	returning the maze and its dimensions
//	The height of the maze is not actually used anywhere but here

int LoadMaze(Maze maze, int& width, int& height, char fname[])
{
	ifstream ifs(fname);

	if (ifs.good())
	{
		ifs >> width >> height;
		if (width * height > 400)
		{
			cout << "This maze is too big" << endl;
			return 0;
		}
		int count = 0;
		for (int i = 0;i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				ifs >> maze[count++];
			}
				
		}

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
	
void FindEntrance(Maze maze, int& pos)
{
	pos = 0;
	
	while (Wall(maze,pos)) pos++;
}

//	This function returns TRUE if the maze position is the exit
//	identified by the character E

int AtExit(Maze maze, int pos)
{
	return (maze[pos] == 'E');
}

//	This function displays the position in the maze
//	At this time it specifies row and column of the array

void ReportPosition(Maze maze, int pos, int width)
{
	int v = 0;
	int h = 0;
	v = pos / width;
	h = pos - (width * v);
	cout << "Current position: (" << v << ',' << h << ')' << endl;
}


//	This function returns TRUE if maze position is wall

int Wall(Maze maze, int pos)
{
	return (maze[pos] == '#');
}

//	This function changes heading by turning right

void TurnRight(Direction& heading)
{
	heading = Direction((int(heading)+1)%4);
}

//	This function changes position in the maze by determining
//	the next position in the current direction

int MoveForward(int width, int& pos, Direction heading)
{
	int ahead;
	WheresAhead(width,pos,heading,ahead);
	return ahead;

}

//	This function determines the position in the direction
//	currently heading

void WheresAhead(int width, int pos, Direction heading, int& ahead)
{
	ahead = pos;
	switch (heading)
	{
		case DOWN:
			ahead += width;
			break;
		case LEFT:
			ahead--;
			break;
		case UP:
			ahead -= width;
			break;
		case RIGHT:
			ahead++;
	}
}

