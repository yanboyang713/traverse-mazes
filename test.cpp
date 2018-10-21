/********************************
*Filename:step3.cpp		*
*Login:by932			*								
*AssignmentNo:ass2		*
*DateLastModified:11/9/2014	*							
********************************/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

//	The following enumerated type indicates directions within the maze

enum Direction {DOWN, LEFT, UP, RIGHT};



//	This struct is used for locations within the maze

struct Position
{
	int H, V;
};

struct list
{
	Position name;
	list* next;
};							//structure for nodes in linked list

typedef char Maze[400][400];
//	These functions provide access to the maze
//	as well as provide manipulation of direction
//	of motion and maze location
//	See implementation for details

list* head;					//head of list
void initialise();
void insertion(Position);		// inserts a node at the end of list
void DisplayList ();
Position *resizeArray(Position *source, int len);
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
int rmback();

int main()
{	

	Maze maze;
	int mazeWidth, mazeHeight;
	Position pos, other;
	Direction heading;
	char fname[20];
	int step = 0;
		
	cout << "Maze File: ";
	cin >> fname;
	LoadMaze(maze,mazeWidth,mazeHeight,fname);
	
	FindEntrance(maze,pos);
	heading = DOWN;
	initialise();			// initialise the list which is global
	while (!AtExit(maze,pos))
	{
		ReportPosition(maze,pos,mazeWidth);
		
		step++;
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
			{
				MoveForward(mazeWidth,pos,heading);
				
			}				
			else
			{
				
				TurnLeft(heading);
				
			}				
		}
	}
	
	DisplayList();
	int temp;
	temp = rmback();
	if (temp == 0)
	{
		return 0;
	}
	
	cout << "\nMaze solved" << endl;
	
	return 0;
}
int rmback()
{
	//remove the backtracking	
	if (head == NULL)
	{
		cout << "The list is empty.." << endl;
	}
	else
	{
		list * ptr = head;
		while (ptr != NULL) 
		{			
			list * temp = ptr->next;
			while (temp != NULL) 
			{
				if ((&ptr->name)->H == (&temp->name)->H && (&ptr->name)->V == (&temp->name)->V)
				{
					list* del = ptr->next;
					//jump
					ptr->next = temp->next;
					//avoid memory leak
					while ((&ptr->name)->H != (&temp->name)->H && (&ptr->name)->V != (&temp->name)->V)
					{
						
						list* tmp;
						tmp = del->next;
						delete del;
						del = tmp;
					}
					if (temp == NULL)
					{
						return 0;
					}					
				}
				
				temp = temp->next;
			}
			ptr = ptr->next;	
		}
		
	}
	return 0;

}
// show the shortest step.

void DisplayList ()
{
	list * ptr = head;
	int i = 0;
	while (ptr != NULL) 
	{
		i++;
		cout << "The step is: ";
		cout << i << " ";
		cout << "Current position: (" << (&ptr->name)->V << ',' << (&ptr->name)->H << ')' << endl;
		ptr = ptr->next;
		
	}
}

void initialise()
{
	head = NULL;			// the head of the list points to nothing
}

// function to insert data into a list

void insertion(Position slist)
{
	list* tmp = new list;

	if (tmp == NULL)
	{
		return;
	}

	tmp->name = slist;
	
	tmp->next = NULL;

	if (head == NULL)		// our node becomes head
	{
		head = tmp;
	}
	else
	{
		list* curr = head;
		while (curr->next != NULL)
		{
			curr = curr->next;
		}
		curr->next = tmp;
	}
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

int LoadMaze(Maze maze, int& width, int& height, char fname[])
{
	ifstream ifs(fname);
	if (ifs.good())
	{
		ifs >> width >> height;
		if (width > 400 || height > 400)
		{
			cerr << "The maze are too bigger" << endl;
			return 0;
		}
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
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

//	This function scans the maze array for the first non-wall list
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
	insertion(pos);		//insertion pos to list	
}


//	This function returns TRUE if maze position is wall

int Wall(Maze maze, Position pos)
{
	return (maze[pos.V][pos.H] == '#');
}

//	This function changes heading by turning right

void TurnRight(Direction& heading)
{
	heading = Direction((int(heading) + 1) % 4);
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

void WheresAhead(int width, Position pos, Direction heading, Position& ahead)
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

