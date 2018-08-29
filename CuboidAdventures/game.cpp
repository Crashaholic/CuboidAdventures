#include "game.h"

Console game(500, 150, "Cuboid Adventures");
Loaded loaded;

Entity player;
SHORT cubeX, cubeY = 1;
bool flip = false;

void init()
{
	game.changeFont(0, 5, L"Consolas");
	loadRequiredFiles();
}

void update()
{
	if (cubeY < 1 || cubeY > 100)
	{
		flip = !flip;
	}

	if (!flip)
	{
		cubeY++;
	}
	else
	{
		cubeY--;
	}
}

void render()
{
	game.clearBuffer();
	renderCube();
	renderPlayer();
	game.bufferToConsole();
}

void loadRequiredFiles()
{
	getPixelDataFromFile("cuboidbase.pixel", &loaded.PlayerChar);
	getPixelDataFromFile("cube.pixel", &loaded.CUBE);
}

void renderPlayer()
{
	COORD offset = { 0, 0 };
	displayPixelVector(&game, offset, &loaded.PlayerChar);
}

void renderCube()
{
	COORD offset = { cubeX, cubeY };
	displayPixelVector(&game, offset, &loaded.CUBE);
}