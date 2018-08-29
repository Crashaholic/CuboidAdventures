#pragma once
#include "console.h"
#include "pixel.h"
#include "Entity.h"
#include <vector>

extern bool bQuitGame;

struct Loaded
{
	std::vector<Pixel> PlayerChar;
	std::vector<Pixel> CUBE;
};

void init();
void update();
void render();

void loadRequiredFiles();
void renderPlayer();
void renderCube();