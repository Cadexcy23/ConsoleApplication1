// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <string>


// function prototypes \/
void draw();
// function prototypes /\



HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
// keep track of the game
bool running = true, update = true;
// keep track of what keys are being pressed
bool pressedLeft = false, pressedRight = false, pressedUp = false, pressedDown = false, pressedSpace = false, pressedI = false, pressed0 = false, pressed1 = false, pressed2 = false, pressed3 = false, pressed4 = false;
// keeps track of the players position
int playerX = 5, playerY = 5;
// keeps track of if the player is allowed to move
bool canMove = true;
// keeps track of the way the player is facing. 1 = Left, 2 = Right, 3 = Up, 4 = Down
int direction = 3;
// keeps track of what spot is infront of the player
int frontOfPlayerX, frontOfPlayerY;
// keeps track of ther camera offset
int cameraOffsetX = 0, cameraOffsetY = 0;
// keeps track of what crafting building you are using if any
int anvilState = 0, inventoryState = 0;
bool inFurnace = false, inBank = false;
// keeps track of what inventory/bank item u select
int row, column;
// keeps track of quest progress
int quest1 = 0;
// Holds items so you can come back later for them
int bank[9][4] = {  { 0,0,0,0 },
					{ 0,0,0,0 },
					{ 0,0,0,0 },
					{ 0,0,0,0 },
					{ 0,0,0,0 },
					{ 0,0,0,0 },
					{ 0,0,0,0 },
					{ 0,0,0,0 },
					{ 0,0,0,0 } };
// Holds all ur items
int inventory[4][4] = { { 5,0,0,0 },
						{ 0,0,0,0 }, 
						{ 0,0,0,0 }, 
						{ 0,0,0,0 }, };
// changes the size of the map
int mapSizeX = 25, mapSizeY = 25;
// defines what the map is
int map[25][25] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					{ 0,9,9,9,1,7,1,8,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,0 },
					{ 0,9,10,9,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0 },
					{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,2,4,4,4,4,4,0,1,0 },
					{ 0,12,1,1,1,1,1,1,1,1,1,1,1,1,1,0,4,4,4,4,4,4,0,1,0 },
					{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,5,0,1,0 },
					{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
					{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
					{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
					{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
					{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
					{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
					{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
					{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
					{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
					{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
					{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
					{ 0,1,0,4,4,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
					{ 0,1,0,4,4,4,4,4,4,4,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
					{ 0,1,0,4,4,4,4,4,4,4,4,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
					{ 0,1,0,11,11,0,4,4,4,4,4,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
					{ 0,1,0,2,2,0,4,4,4,4,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
					{ 0,1,0,0,0,0,0,0,4,4,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
					{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
					{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },};


void drawAnvil()
{
	system("cls");
	SetConsoleTextAttribute(hConsole, 8);
	std::cout << "     __________\n";
	std::cout << " ___/        _/\n";
	std::cout << " \\__       _/  \n";
	std::cout << "    \\     /  \n";
	std::cout << "     )   (    \n";
	std::cout << "    /     \\  \n";
	std::cout << "   |___^___|      Anvil:\n";
}

void openAnvilWindow()
{
	drawAnvil();
	anvilState = 1;
	canMove = false;
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << "\nWhat material would you like to use?\n 1 = Bronze\n 2 = Iron\n 3 = Steel\n 4 = Gold\n 0 = Exit\n";
	
}

void withdrawItemFromBank(int item)
{
	bool found = false, placed = false;
	//find item in bank
	for (int a = 0; a <= 8; a++)
	{
		for (int b = 0; b <= 3; b++)
		{
			if (bank[a][b] == item && !found)
			{
				found = true;
				for (int a = 0; a <= 3; a++)
				{
					for (int b = 0; b <= 3; b++)
					{
						if (inventory[a][b] == 0 && !placed)
						{
							//put it to inventory
							placed = true;
							inventory[a][b] = item;
						}
					}
				}
				//remove from bank
				bank[a][b] = 0;
				return;
			}
		}
	}
}

void depositItemInBank(int item)
{
	bool found = false, placed = false;
	//find item in inventory
	for (int a = 0; a <= 3; a++)
	{
		for (int b = 0; b <= 3; b++)
		{
			if (inventory[a][b] == item && !found)
			{
				found = true;
				for (int a = 0; a <= 8; a++)
				{
					for (int b = 0; b <= 3; b++)
					{
						if (bank[a][b] == 0 && !placed)
						{
							//put it to bank
							placed = true;
							bank[a][b] = item;
						}
					}
				}
			//remove from inventory
			inventory[a][b] = 0;
			return;
			}
		}
	}
	
	
}

void drawEmptySpace(int amount)
{
	int count = 0;
	while (count < amount)
	{
		std::cout << ' ';
		count++;
	}
}

std::string getItemName(int item)
{
	switch (item)
	{
	case 0:
		return "empty";
		break;
	case 1:
		return "Piggie slipper";
		break;
	case 2:
		return "Pickaxe";
		break;
	case 3:
		return "Tin Ore";
		break;
	case 4:
		return "Copper Ore";
		break;
	case 5:
		return "Bronze Bar";
		break;
	case 6:
		return "Bronze Dagger";
		break;
	}

}

void openBankWindow()
{
	int count = 1;
	inBank = true;
	canMove = false;
	// draw ASCII art
	system("cls");
	SetConsoleTextAttribute(hConsole, 14);
	std::cout << "Bank:\n";
	SetConsoleTextAttribute(hConsole, 15);
	for (int a = 0; a <= 8; a++)
	{
		for (int b = 0; b <= 3; b++)
		{
			if (b == 0)
			{
				std::cout << "\n";
				std::cout << count << ":";
				count++;
			}


			std::string item = getItemName(bank[a][b]);
			int length = item.length();
			std::cout << item;
			drawEmptySpace(20 - length - 1);
		}
	}
	std::cout << "\n\nWhat would you like to do?\n 1 = Deposit all\n 2 = Deposit item\n 3 = Withdraw item\n 0 = Exit\n";

}

void drawFurnace()
{
	system("cls");
	SetConsoleTextAttribute(hConsole, 8);
	std::cout << "___________________\n";
	std::cout << "|#################|\n";
	SetConsoleTextAttribute(hConsole, 8);
	std::cout << "|#|             |#|\n";
	std::cout << "|#|             |#|\n";
	std::cout << "|#|             |#|\n";
	std::cout << "|#|";
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "_____________";
	SetConsoleTextAttribute(hConsole, 8);
	std::cout << "|#|\n";
	std::cout << "|#|";
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "#############";
	SetConsoleTextAttribute(hConsole, 8);
	std::cout << "|#|\n";
	std::cout << "|#|";
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "#############";
	SetConsoleTextAttribute(hConsole, 8);
	std::cout << "|#|\n";
	std::cout << "|######";
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "|###|";
	SetConsoleTextAttribute(hConsole, 8);
	std::cout << "######|\n";
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "       |###|";
	SetConsoleTextAttribute(hConsole, 4);
	std::cout << "       Furnace:\n";
	SetConsoleTextAttribute(hConsole, 15);
}

void openFurnaceWindow()
{
	inFurnace = true;
	canMove = false;
	drawFurnace();
	std::cout << "\nWhat would you like to smelt?\n 1 = Bronze \n 2 = Iron\n 3 = Steel\n 4 = Gold\n 0 = Exit\n";
}

void removeItemFromInventory(int item)
{
	bool found = false;
	for (int a = 0; a <= 3; a++)
	{
		for (int b = 0; b <= 3; b++)
		{
			if (inventory[a][b] == item && !found)
			{
				inventory[a][b] = 0;
				found = true;
				return;
			}
		}
	}
	return;
}

bool addItemToInventory(int item)
{
	bool found = false;
	for (int a = 0; a <= 3; a++)
	{
		for (int b = 0; b <= 3; b++)
		{
			if (inventory[a][b] == 0 && !found)
			{
				inventory[a][b] = item;
				found = true;
				return true;
			}
		}
	}
	return false;
}

bool checkInventoryForItem(int item)
{
	bool found = false;
	for (int a = 0; a <= 3; a++)
	{
		for (int b = 0; b <= 3; b++)
		{
			if (inventory[a][b] == item && !found)
			{
				found = true;
				return true;
			}
		}
	}
	return false;
}

void drawBag()
{
	system("cls");
	SetConsoleTextAttribute(hConsole, 6);
	std::cout << "    __    \n";
	std::cout << " __/__\\__\n";
	std::cout << "|        |\n";
	std::cout << "|________|\n";
	std::cout << "(___II___)\n";
	std::cout << "|        |\n";
	std::cout << "|________|";
	SetConsoleTextAttribute(hConsole, 14);
	std::cout << "   Inventory:\n";
	SetConsoleTextAttribute(hConsole, 15);
}

void drawInventory()
{
	int count = 1;
	canMove = false;
	drawBag();
	std::cout << "\n";
	for (int a = 0; a <= 3; a++)
	{
		for (int b = 0; b <= 3; b++)
		{
			if (b == 0)
			{
				std::cout << "\n";
				std::cout << count << ":";
				count++;
			}


			std::string item = getItemName(inventory[a][b]);
			int length = item.length();
			std::cout << item;
			drawEmptySpace(20 - length - 1);
		}
	}
}

void openInventory()
{
	if (canMove)
	{
		drawInventory();
		inventoryState = 1;
		std::cout << "\n\nWhat would you like to do?\n 1 = Equip item\n 2 = Drop(destroy) item\n 3 = Move item\n 0 = Exit";
	}
}

void drawFace()
{
	SetConsoleTextAttribute(hConsole, 6);
		std::cout << "  __________\n";
		std::cout << " /          \\\n";
		std::cout << "/            \\\n";
		std::cout << "|             |\n";
		std::cout << "|   <>   <>   |\n";
		std::cout << "|   _______   |\n";
		std::cout << "|   \\     /   |\n";
		std::cout << "|    \\___/    |\n";
		std::cout << "\\            /\n";
		std::cout << " \\__________/\n";
	SetConsoleTextAttribute(hConsole, 15);
}

void talkToNPC()
{
	system("cls");
	drawFace();
	if (quest1 == 0)
	{
		std::cout << "\nNPC: Hey I lost my ";
		SetConsoleTextAttribute(hConsole, 13);
		std::cout << "Piggie Slipper ";
		SetConsoleTextAttribute(hConsole, 15);
		std::cout << "could you find it for me?\n";
		quest1 = 1;
		system("PAUSE");
		return;
	}
	if (quest1 == 1 && checkInventoryForItem(1))
	{
		std::cout << "\nNPC: You found my beloved ";
		SetConsoleTextAttribute(hConsole, 13);
		std::cout << "Piggie Slipper";
		SetConsoleTextAttribute(hConsole, 15);
		std::cout << "! Here, Take this pickaxe. I'm sure you can use it better than me.\n";
		if (addItemToInventory(2))
		{
			removeItemFromInventory(1);
			quest1 = 2;
		}
		else
		{
			std::cout << "\nNPC: Looks like your inventory is full. Come back then you have room.\n";
		}
		system("PAUSE");
		return;
	}
	if (quest1 == 1)
	{
		std::cout << "\nNPC: Have you found my ";
		SetConsoleTextAttribute(hConsole, 13);
		std::cout << "Piggie Slipper ";
		SetConsoleTextAttribute(hConsole, 15);
		std::cout << "yet? No? Keep looking.\n";
		system("PAUSE");
		return;
	}
	if (quest1 == 2)
	{
		std::cout << "\nNPC: Okay you helped me can you leave my house now?\n";
		system("PAUSE");
		return;
	}
}

void interact()
{
	// font what spot is infront of the player
	switch (map[frontOfPlayerY][frontOfPlayerX])
	{
	// wall
	case 0:
		break;
	// grass
	case 1:
		break;
	// person
	case 2:
		talkToNPC();
		break;
	// Piggies slipper
	case 3:
		//system("PAUSE");
		addItemToInventory(1);
		map[frontOfPlayerY][frontOfPlayerX] = 1;
		update = true;
		draw();
		std::cout << "\nYou pick up a Piggie Slipper.\n";
		break;
	// floor
	case 4:
		break;
	// closed door
	case 5:
		map[frontOfPlayerY][frontOfPlayerX] = 6;
		update = true;
		break;
	// open door
	case 6:
		map[frontOfPlayerY][frontOfPlayerX] = 5;
		update = true;
		break;
	// tin rock
	case 7:
		if (checkInventoryForItem(2))
		{
			if (addItemToInventory(3)) 
			{
				std::cout << "\nYou mine some Tin.\n";
			}
			else
			{
				std::cout << "\nYou need room in your inventory to mine this rock.\n";
			}
		}
		else
		{
			std::cout << "\nYou need a pickaxe to mine this rock.\n";
		}
		break;
	// copper rock
	case 8:
		if (checkInventoryForItem(2))
		{
			if (addItemToInventory(4))
			{
				std::cout << "\nYou mine some Copper.\n";
			}
			else
			{
				std::cout << "\nYou need room in your inventory to mine this rock.\n";
			}
		}
		else
		{
			std::cout << "\nYou need a pickaxe to mine this rock.\n";
		}
		break;
	// furnace case
	case 9:
		std::cout << "\nTry using the front.";
		break;
	// furnace openning
	case 10:
		openFurnaceWindow();
		break;
	// bank desk
	case 11:
		openBankWindow();
		break;
	// anvil
	case 12:
		openAnvilWindow();
		break;
	}
	
}

// checks if you can walk on a tile
bool isWalkable(int x,int y)
{
	// add to make other tiles have colision
	if (map[y][x] == 0 || map[y][x] == 2 || map[y][x] == 3 || map[y][x] == 5 || map[y][x] == 7 || map[y][x] == 8 || map[y][x] == 9 || map[y][x] == 10 || map[y][x] == 11 || map[y][x] == 12)
		return false;
	else
		return true;
}

void movePlayer(int x, int y)
{
	// make sure he isnt coliding with anything
	if (isWalkable(playerX + x, playerY) && isWalkable(playerX, playerY + y) && canMove)
	{
		playerX = playerX + x;
		playerY = playerY + y;
		update = true;
	}
}

// get tile to draw
char getTileChar(int row, int column)
{
	if (row > mapSizeY-1 || row < 0 || column > mapSizeX-1 || column < 0)
		return ' ';
	switch (map[row][column])
	{
	//wall
	case 0:
		SetConsoleTextAttribute(hConsole, 7);
		return '#';
	//grass
	case 1:
		SetConsoleTextAttribute(hConsole, 2);
		return '#';
	//person
	case 2:
		SetConsoleTextAttribute(hConsole, 6);
		return '0';
	//piggie slipper
	case 3:
		SetConsoleTextAttribute(hConsole, 5);
		return 'p';
	//floor
	case 4:
		SetConsoleTextAttribute(hConsole, 8);
		return '#';
	//closed door
	case 5:
		SetConsoleTextAttribute(hConsole, 7);
		return '_';
	//open door
	case 6:
		SetConsoleTextAttribute(hConsole, 7);
		return '/';
	//tin rock
	case 7:
		SetConsoleTextAttribute(hConsole, 8);
		return 'n';
	//copper rock
	case 8:
		SetConsoleTextAttribute(hConsole, 6);
		return 'n';
	// furnace case
	case 9:
		SetConsoleTextAttribute(hConsole, 8);
		return '=';
	// furnace openning
	case 10:
		SetConsoleTextAttribute(hConsole, 4);
		return '+';
	// bank desk
	case 11:
		SetConsoleTextAttribute(hConsole, 4);
		return 'T';
	// anvil
	case 12:
		SetConsoleTextAttribute(hConsole, 8);
		return 'r';
	}

}

void controller()
{
	// only activates once per click
	// left
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		if (GetKeyState(VK_LEFT) & 0x8000 && !pressedLeft)
		{
			pressedLeft = true;
			
			// put what hitting left does here
			movePlayer(-1, 0);
			direction = 1;

			return;
		}
	}
	else
	{		
		pressedLeft = false;
	}

	// right
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		if (GetKeyState(VK_RIGHT) & 0x8000 && !pressedRight)
		{
			pressedRight = true;
			
			// put what hitting right does here
			movePlayer(1, 0);
			direction = 2;

			return;
		}
	}
	else
	{
		pressedRight = false;
	}

	// up
	if (GetKeyState(VK_UP) & 0x8000)
	{
		if (GetKeyState(VK_UP) & 0x8000 && !pressedUp)
		{
			pressedUp = true;
			
			// put what hitting left does here
			movePlayer(0, -1);
			direction = 3;

			return;
		}
	}
	else
	{
		pressedUp = false;
	}

	// down
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		if (GetKeyState(VK_DOWN) & 0x8000 && !pressedDown)
		{
			pressedDown = true;
			
			// put what hitting Down does here
			movePlayer(0, 1);
			direction = 4;

			return;
		}
	}
	else
	{
		pressedDown = false;
	}
	
	// space
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		if (GetKeyState(VK_SPACE) & 0x8000 && !pressedSpace)
		{
			pressedSpace = true;

			// put what hitting space does here
			interact();

			return;
		}
	}
	else
	{
		pressedSpace = false;
	}

	// I
	if (GetKeyState(0x49) & 0x8000)
	{
		if (GetKeyState(0x49) & 0x8000 && !pressedI)
		{
			pressedI = true;

			// put what hitting I does here
			openInventory();

			return;
		}
	}
	else
	{
		pressedI = false;
	}

	// 0
	if (GetKeyState(0x30) & 0x8000)
	{
		if (GetKeyState(0x30) & 0x8000 && !pressed0)
		{
			pressed0 = true;

			// put what hitting 0 does here
			update = true;
			canMove = true;
			inBank = false;
			inFurnace = false;
			inventoryState = 0;
			anvilState = 0;
			return;
		}
	}
	else
	{
		pressed0 = false;
	}

	// 1
	if (GetKeyState(0x31) & 0x8000)
	{
		if (GetKeyState(0x31) & 0x8000 && !pressed1)
		{
			pressed1 = true;

			// put what hitting 1 does here
			
			return;
		}
	}
	else
	{
		pressed1 = false;
	}

	// 2
	if (GetKeyState(0x32) & 0x8000)
	{
		if (GetKeyState(0x32) & 0x8000 && !pressed2)
		{
			pressed2 = true;

			// put what hitting 2 does here
			
			return;
		}
	}
	else
	{
		pressed2 = false;
	}

	// 3
	if (GetKeyState(0x33) & 0x8000)
	{
		if (GetKeyState(0x33) & 0x8000 && !pressed3)
		{
			pressed3 = true;

			// put what hitting 3 does here
			
			return;
		}
	}
	else
	{
		pressed3 = false;
	}

	// 4
	if (GetKeyState(0x34) & 0x8000)
	{
		if (GetKeyState(0x34) & 0x8000 && !pressed4)
		{
			pressed4 = true;

			// put what hitting 4 does here
			
			return;
		}
	}
	else
	{
		pressed4 = false;
	}
}



void logic()
{
	cameraOffsetX = playerX - 10;
	cameraOffsetY = playerY - 5;

	frontOfPlayerX = playerX;
	frontOfPlayerY = playerY;
	switch (direction)
	{
	case 1:
		frontOfPlayerX = playerX - 1;
		break;
	case 2:
		frontOfPlayerX = playerX + 1;
		break;
	case 3:
		frontOfPlayerY = playerY - 1;
		break;
	case 4:
		frontOfPlayerY = playerY + 1;
		break;
	}

	
	
	// in inventory
	if (inventoryState > 0)
	{
		// 1 is pressed
		if (pressed1 && inventoryState == 1)
		{
			std::cout << "\nLUL";
			inventoryState = 0;
		}

		// 2 is pressed
		if (pressed2 && inventoryState == 1)
		{
			
			pressed2 = false;
			drawInventory();
			Sleep(500);
			std::cout << "\n\nDropping item";
			std::cout << "\nWhat row?\n";
			inventoryState = 20;
			
		}
		//in drop 
		if (inventoryState >= 20 && inventoryState < 30)
		{
			
			// select row
			if (inventoryState == 20)
			{
				if (pressed1)
				{
					row = 1;
					std::cout << row << "\nWhat column?\n";
					inventoryState = 21;
					Sleep(500);
					pressed1 = false;
				}
				if (pressed2)
				{
					row = 2;
					std::cout << row << "\nWhat column?\n";
					inventoryState = 21;
					Sleep(500);
					pressed2 = false;
				}
				if (pressed3)
				{
					row = 3;
					std::cout << row << "\nWhat column?\n";
					inventoryState = 21;
					Sleep(500);
					pressed3 = false;
				}
				if (pressed4)
				{
					row = 4;
					std::cout << row << "\nWhat column?\n";
					inventoryState = 21;
					Sleep(500);
					pressed4 = false;
				}
			}
			// select column
			if (inventoryState == 21)
			{
				
					if (pressed1)
					{
						column = 1;
						std::cout << column;
						inventoryState = 22;
						Sleep(500);
						pressed1 = false;
					}
					if (pressed2)
					{
						column = 2;
						std::cout << column;
						inventoryState = 22;
						Sleep(500);
						pressed2 = false;
					}
					if (pressed3)
					{
						column = 3;
						std::cout << column;
						inventoryState = 22;
						Sleep(500);
						pressed3 = false;
					}
					if (pressed4)
					{
						column = 4;
						std::cout << column;
						inventoryState = 22;
						Sleep(500);
						pressed4 = false;
					}
				
			}
			// finishing up
			if (inventoryState == 22)
			{
				removeItemFromInventory(inventory[row-1][column-1]);
				drawInventory();
				std::cout << "\n\nItem dropped. Press 0 to exit.";
				inventoryState = 0;
			}
			
		}
		

		// 3 is pressed
		if (pressed3 && inventoryState == 1)
		{
			std::cout << "\nLUL";
			inventoryState = 0;
		}
	}

	// in furnace
	if (inFurnace)
	{
		// 1 is pressed
		if (pressed1)
		{
			if (checkInventoryForItem(3) && checkInventoryForItem(4))
			{
				removeItemFromInventory(3);
				removeItemFromInventory(4);
				addItemToInventory(5);
				inFurnace = false;
				std::wcout << "You put the Tin and Copper in and make a Bronze Bar.\nPress space to make something else or press 0 to exit.\n";
			}
			else
			{
				inFurnace = false;
				std::wcout << "You need Tin and Copper to make Bronze.\nPress space to make something else or press 0 to exit.\n";
			}
		}
		// 2 is pressed
		if (pressed2)
		{
			inFurnace = false;
			std::wcout << "This feature is currently not available.\nPress space to make something else or press 0 to exit.\n";
			/*if (checkInventoryForItem(3) && checkInventoryForItem(4))
			{
				removeItemFromInventory(3);
				removeItemFromInventory(4);
				addItemToInventory(5);
				inFurnace = false;
				std::wcout << "You put the Tin and Copper in and make a Bronze Bar.\nPress space to make something else or press 0 to exit.\n";
			}
			else
			{
				inFurnace = false;
				std::wcout << "You need Tin and Copper to make Bronze.\nPress space to make something else or press 0 to exit.\n";
			}*/
		}
		// 3 is pressed
		if (pressed3)
		{
			inFurnace = false;
			std::wcout << "This feature is currently not available.\nPress space to make something else or press 0 to exit.\n";
			/*if (checkInventoryForItem(3) && checkInventoryForItem(4))
			{
			removeItemFromInventory(3);
			removeItemFromInventory(4);
			addItemToInventory(5);
			inFurnace = false;
			std::wcout << "You put the Tin and Copper in and make a Bronze Bar.\nPress space to make something else or press 0 to exit.\n";
			}
			else
			{
			inFurnace = false;
			std::wcout << "You need Tin and Copper to make Bronze.\nPress space to make something else or press 0 to exit.\n";
			}*/
		}
		// 4 is pressed
		if (pressed4)
		{
			inFurnace = false;
			std::wcout << "This feature is currently not available.\nPress space to make something else or press 0 to exit.\n";
			/*if (checkInventoryForItem(3) && checkInventoryForItem(4))
			{
			removeItemFromInventory(3);
			removeItemFromInventory(4);
			addItemToInventory(5);
			inFurnace = false;
			std::wcout << "You put the Tin and Copper in and make a Bronze Bar.\nPress space to make something else or press 0 to exit.\n";
			}
			else
			{
			inFurnace = false;
			std::wcout << "You need Tin and Copper to make Bronze.\nPress space to make something else or press 0 to exit.\n";
			}*/
		}
	}

	// in bank
	if (inBank)
	{
		// when 1 is pressed
		if (pressed1)
		{
			for (int a = 0; a <= 3; a++)
			{
				for (int b = 0; b <= 3; b++)
				{
					if (inventory[a][b] != 0)
					{
						depositItemInBank(inventory[a][b]);
					}
				}
			}
			openBankWindow();
			inBank = false;
			std::cout << "All items placed in the bank.";
		}

		// when 2 is pressed
		if (pressed2)
		{
			inBank = false;

			int row, column;

			canMove = true;
			drawInventory();
			canMove = false;

			std::cout << "\n\nDepositing item.\n";
			std::cout << "Which row?" << std::endl;
			std::cin >> row;
			std::cout << "Which column?" << std::endl;
			std::cin >> column;
			
			

			depositItemInBank(inventory[row - 1][column - 1]);
			openBankWindow();
			inBank = false;

			std::cout << "Item deposited.";
		}

		// when 3 is pressed
		if (pressed3)
		{
			inBank = false;

			int row, column;

			
			std::cout << "Withdrawing item.\n";
			std::cout << "Which row?" << std::endl;
			std::cin >> row;
			std::cout << "Which column?" << std::endl;
			std::cin >> column;
			
			

			withdrawItemFromBank(bank[row-1][column-1]);
			openBankWindow();
			inBank = false;
			
			std::cout << "Item withdrawn.";
		}
	}

	// in anvil
	if (anvilState > 0)
	{
		//bool anvilPress = false;
		// 1 is pressed
		if (pressed1 && anvilState == 1)
		{
			anvilState = 10;
			drawAnvil();
			SetConsoleTextAttribute(hConsole, 15);
			Sleep(500);
			std::cout << "\nUsing Bronze. What would you like to make?\n 1 = Dagger\n 2 = Sword\n 3 = Shield\n 4 = More options\n 0 = Exit\n";
			pressed1 = false;
		}
		// 1 is pressed in bronze state
		if (pressed1 && anvilState == 10)
		{
			if (checkInventoryForItem(5))
			{
				anvilState = 0;
				removeItemFromInventory(5);
				addItemToInventory(6);
				std::cout << "\nYou make a Bronze Dagger. \nPress space to make something else or press 0 to exit.\n";
			}
			else
			{
				std::cout << "\nYou need a Bronze Bar to make a Bronze Dagger. \nPress space to make something else or press 0 to exit.\n";
				anvilState = 0;
			}
		}

		// 2 is pressed in bronze state
		if (pressed2 && anvilState == 10)
		{
			std::cout << "\nThis feature is currently not available.\nPress space to make something else or press 0 to exit.\n";
			anvilState = 0;
			/*if (checkInventoryForItem(5))
			{
				anvilState = 0;
				removeItemFromInventory(5);
				addItemToInventory(6);
				std::cout << "\nYou make a Bronze Dagger. \nPress space to make something else or press 0 to exit.\n";
			}
			else
			{
				std::cout << "\nYou need a Bronze Bar to make a Bronze Dagger. \nPress space to make something else or press 0 to exit.\n";
				anvilState = 0;
			}*/
		}

		// 3 is pressed in bronze state
		if (pressed3 && anvilState == 10)
		{
			std::cout << "\nThis feature is currently not available.\nPress space to make something else or press 0 to exit.\n";
			anvilState = 0;
			/*if (checkInventoryForItem(5))
			{
			anvilState = 0;
			removeItemFromInventory(5);
			addItemToInventory(6);
			std::cout << "\nYou make a Bronze Dagger. \nPress space to make something else or press 0 to exit.\n";
			}
			else
			{
			std::cout << "\nYou need a Bronze Bar to make a Bronze Dagger. \nPress space to make something else or press 0 to exit.\n";
			anvilState = 0;
			}*/
		}

		// 4 is pressed in bronze state
		if (pressed4 && anvilState == 10)
		{
			std::cout << "\nThis feature is currently not available.\nPress space to make something else or press 0 to exit.\n";
			anvilState = 0;
			/*if (checkInventoryForItem(5))
			{
			anvilState = 0;
			removeItemFromInventory(5);
			addItemToInventory(6);
			std::cout << "\nYou make a Bronze Dagger. \nPress space to make something else or press 0 to exit.\n";
			}
			else
			{
			std::cout << "\nYou need a Bronze Bar to make a Bronze Dagger. \nPress space to make something else or press 0 to exit.\n";
			anvilState = 0;
			}*/
		}

		// 2 is pressed
		if (pressed2 && anvilState == 1)
		{
			std::cout << "\nThis feature is currently not available.\nPress space to make something else or press 0 to exit.\n";

			anvilState = 20;
			/*drawAnvil();
			SetConsoleTextAttribute(hConsole, 15);
			Sleep(500);
			std::cout << "\nUsing Iron. What would you like to make?\n 1 = Dagger\n 2 = Sword\n 3 = Shield\n 4 = More options\n 0 = Exit\n";
			pressed2 = false;*/
		}

		// 3 is pressed
		if (pressed3 && anvilState == 1)
		{
			std::cout << "\nThis feature is currently not available.\nPress space to make something else or press 0 to exit.\n";

			anvilState = 30;
			/*drawAnvil();
			SetConsoleTextAttribute(hConsole, 15);
			Sleep(500);
			std::cout << "\nUsing Iron. What would you like to make?\n 1 = Dagger\n 2 = Sword\n 3 = Shield\n 4 = More options\n 0 = Exit\n";
			pressed3 = false;*/
		}

		// 4 is pressed
		if (pressed4 && anvilState == 1)
		{
			std::cout << "\nThis feature is currently not available.\nPress space to make something else or press 0 to exit.\n";

			anvilState = 40;
			/*drawAnvil();
			SetConsoleTextAttribute(hConsole, 15);
			Sleep(500);
			std::cout << "\nUsing Iron. What would you like to make?\n 1 = Dagger\n 2 = Sword\n 3 = Shield\n 4 = More options\n 0 = Exit\n";
			pressed4 = false;*/
		}
	}
}



void draw() 
{
	
	// true = display color names
	if (false)
	{
		SetConsoleTextAttribute(hConsole, 1);
		std::cout << "#1 Dark Blue\n";
		SetConsoleTextAttribute(hConsole, 2);
		std::cout << "#2 Dark Green\n";
		SetConsoleTextAttribute(hConsole, 3);
		std::cout << "#3 Dark Light Blue\n";
		SetConsoleTextAttribute(hConsole, 4);
		std::cout << "#4 Dark Red\n";
		SetConsoleTextAttribute(hConsole, 5);
		std::cout << "#5 Dark Purple\n";
		SetConsoleTextAttribute(hConsole, 6);
		std::cout << "#6 Dark Yellow\n";
		SetConsoleTextAttribute(hConsole, 7);
		std::cout << "#7 Dark White\n";
		SetConsoleTextAttribute(hConsole, 8);
		std::cout << "#8 Grey\n";
		SetConsoleTextAttribute(hConsole, 9);
		std::cout << "#9 Blue\n";
		SetConsoleTextAttribute(hConsole, 10);
		std::cout << "#10 Green\n";
		SetConsoleTextAttribute(hConsole, 11);
		std::cout << "#11 Light Blue\n";
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << "#12 Red\n";
		SetConsoleTextAttribute(hConsole, 13);
		std::cout << "#13 Purple\n";
		SetConsoleTextAttribute(hConsole, 14);
		std::cout << "#14 Yellow\n";
		SetConsoleTextAttribute(hConsole, 15);
		std::cout << "#15 White\n";
	}
	if (update)
	{
		system("cls");

		for (int a = 0; a <= 10; a++)
		{
			for (int b = 0; b <= 20; b++)
			{
				int offsetA = a + cameraOffsetY, offsetB = b + cameraOffsetX;
				
				if (b == 10 && a == 5)
				{
					SetConsoleTextAttribute(hConsole, 14);
					std::cout << 0;
				}
				else if (b == 20)
				{
					std::cout << getTileChar(offsetA, offsetB) << '\n';
				}
				else
				{
					std::cout << getTileChar(offsetA, offsetB);
				}
			}
		}
		SetConsoleTextAttribute(hConsole, 15);
		switch (direction)
		{
		case 1:
			std::cout << "\nFacing: Left";
			break;
		case 2:
			std::cout << "\nFacing: Right";
			break;
		case 3:
			std::cout << "\nFacing: Up";
			break;
		case 4:
			std::cout << "\nFacing: Down";
			break;
		}
		std::cout << "\nUse arrow keys to move and space to interact.";
		std::cout << "\nX:" << playerX << " Y:" << playerY;
		std::cout << "\nInteract: X:" << frontOfPlayerX << " Y:" << frontOfPlayerY << "\n";
		

		update = false;
	}
	
}


int main()
{
	while (running)
	{

		controller();
		logic();
		draw();
		
		
		
	}

	return 0;
}