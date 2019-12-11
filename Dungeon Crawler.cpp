#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

const int row = 10;
const int col = 10;
const int traps = 3;
const int monsters = 3;
string dungeonBoard[row][col];
string playermove;
int playerPosition[2];
int trapPosition[traps][2];
int monstersPosition[monsters][2];
int treasurePosition[2];
int StepsCount;
bool exitGame, loopExit;

void DungeonTitle();
void InitDungeon();
void DisplayDungeon();
void SpawnTraps();
void SpawnMonsters();
void PlayerMovement();
void MonstersMovement();

int main()
{
	
	do
	{
		StepsCount = 0;
		exitGame = false;
		loopExit = false;
		srand(time(NULL));
		
		system("CLS");
		InitDungeon();
		SpawnTraps();
		SpawnMonsters();
		dungeonBoard[0][0] = " P";
		playerPosition[0] = 0;
		playerPosition[1] = 0;
		dungeonBoard[9][9] = " X";
		treasurePosition[0] = 9;
		treasurePosition[1] = 9;
		
		do
		{
			system("CLS");
			DungeonTitle();
			DisplayDungeon();
			PlayerMovement();
			MonstersMovement();
			int xM, yM, xT, yT;
			int xP = playerPosition[0], yP = playerPosition[1];
		
			for (int i = 0; i < monsters; i++)
			{
				xM = monstersPosition[i][0];
				yM = monstersPosition[i][1];
				
				if ((xM == xP) && (yM == yP))
				{
					cout << "The monster caught you wandering in its lair and IT WAS NOT HAPPY.\n The monster furiously ripped the meat off your body." << endl;
					loopExit = true;
				} 
			}
			for (int i = 0; i < traps; i++)
			{
				xT = trapPosition[i][0];
				yT = trapPosition[i][1];
				
				if ((xT == xP) && (yT == yP))
				{
					cout << "You triggered a trap and arrows started flying towards you. \nYou fell backwards and you bled to death." << endl;
					loopExit = true;
				}
			}
			if (xP == treasurePosition[0] && yP == treasurePosition[1])
			{
				cout << "You found the treasure and you managed to escape with the loot!!" << endl;
				loopExit = true;
			}
			
		}while(!loopExit);
		
		loopExit = false;
		
		do
		{
			cout << "Do you want to try again ( y / n )" << endl;
			cin >> playermove;
			
			if (playermove == "n")
			{
				cout << "What's the matter? Scared, Potter?" << endl;
				loopExit = true;
				exitGame = true;
			}
			else if(playermove == "y")
			{
				loopExit = true;
			}
			else
			{
				cout << "Invalid input" << endl;
			}
		}while(!loopExit);
		
	}while(!exitGame);
	
	
	system("pause");
	return 0;
}

void DungeonTitle()
{
	cout << " = = = = = = = = = = = =" << endl;
	cout << " =                     =" << endl;
	cout << " =   DUNGEON CRAWLER   =" << endl;
	cout << " =                     =" << endl;
	cout << " = = = = = = = = = = = =" << endl;
	cout << endl;
}

void InitDungeon()
{
	for ( int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			dungeonBoard[j][i] = " -";
		}
	}
}

void DisplayDungeon()
{
	for ( int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			cout << dungeonBoard[j][i];
		}
		cout << endl;
	}
}

void SpawnTraps()
{
	for (int i = 0; i < traps; i++)
	{
		
		
		bool isExit = false;
		
		do 
		{
			int x = rand() % (row - 2) + 1;
			int y = rand() % (col - 2) + 1;
			
			if (dungeonBoard[x][y] == " -")
			{
				dungeonBoard[x][y] = " T";
				trapPosition[i][0] = x;
				trapPosition[i][1] = y;
				isExit = true;
			}
		}while(!isExit);
	}
}

void SpawnMonsters()
{
	for (int i=0; i < monsters; i++)
	{
		bool isExit = false;
		
		do
		{
			int x = rand() % (row - 2) + 1;
			int y = rand() % (col - 2) + 1;
			
			if (dungeonBoard[x][y] == " -")
			{
				dungeonBoard[x][y] = " M";
				monstersPosition[i][0] = x;
				monstersPosition[i][1] = y;
				isExit = true;
			}
			
		}while(!isExit);
	}
}

void PlayerMovement()
{
	bool isExit = false;
	int tempX, tempY;
	int x, y;
	
	cout << "Steps Counter: " << StepsCount << endl;
	do
	{
		tempX = playerPosition[0];
		tempY = playerPosition[1];
		cout << "Where do you want to move? \n";
		cin >> playermove;
		
		if (playermove == "w")
		{
			if (playerPosition[1] <= 0)
			{
				cout << "You cannot move that way. \n";
			}
			else
			{
				playerPosition[1] = tempY - 1;
				isExit= true;
			}
		}
		else if(playermove == "s")
		{
			if (playerPosition[1] >= (row - 1))
			{
				cout << "You cannot move that way. \n";
			}
			else 
			{
				playerPosition[1] = tempY + 1;
				isExit = true;
			}
		}
		else if(playermove == "a")
		{
			if (playerPosition[0] <= 0)
			{
				cout << "You cannot move that way. \n";
			}
			else 
			{
				playerPosition[0] = tempX - 1;
				isExit = true;
			}
		}
		else if(playermove == "d")
		{
			if (playerPosition[0] >= (col - 1))
			{
				cout << "You cannot move that way. \n";
			}
			else
			{
				playerPosition[0] = tempX + 1;
				isExit = true;
			}
		}
		else
		{
			cout << "Invalid input \n";
		}
	}while(!isExit);
	
	StepsCount += 1;
	x = tempX;
	y = tempY;
	
	
	if (dungeonBoard[x][y] == " P")
	{
		dungeonBoard[x][y] = " -";
		isExit = true;
	}
	
	x = playerPosition[0];
	y = playerPosition[1];
	
	dungeonBoard[x][y] = " P";
	
}

void MonstersMovement()
{
	for(int i = 0; i < monsters; i++)
	{
		bool isExit= false;
		int x, y, tempX, tempY;
		
		do
		{
			x = rand() % 4;
			
			
			switch(x)
			{
				case 0:
					if (monstersPosition[i][1] > 0)
					{
						tempY = monstersPosition[i][1] - 1;
						tempX = monstersPosition[i][0];
						isExit = true;
						
					}
					break;
				case 1:
					if (monstersPosition[i][1] < (row - 1))
					{
						tempY = monstersPosition[i][1] + 1;
						tempX = monstersPosition[i][0];
						isExit = true;
					}
					break;
				case 2:
					if (monstersPosition[i][0] > 0)
					{
						tempX = monstersPosition[i][0] - 1;
						tempY = monstersPosition[i][1];
						isExit = true;
					}
					break;
				case 3:
					if (monstersPosition[i][0] < (col - 1))
					{
						tempX = monstersPosition[i][0] + 1;
						tempY = monstersPosition[i][1];
						isExit = true;
					}
					break;
			}
		}while(!isExit);
		
		x = monstersPosition[i][0];
		y = monstersPosition[i][1];
		
		if (dungeonBoard[x][y] == " M")
		{
			dungeonBoard[x][y] = " -";
		}
		
		x = tempX;
		y = tempY;
		
		if (dungeonBoard[x][y] == " -")
		{
			dungeonBoard[x][y] = " M";
		}
		
		monstersPosition[i][0] = x;
		monstersPosition[i][1] = y;
	}
}





