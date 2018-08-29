#pragma once
#ifndef PIXELHEAD
#define PIXELHEAD
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "console.h"

struct Pixel
{
	COORD coord;
	WORD attrib;
};

void getPixelDataFromFile(std::string fileName, std::vector<Pixel> *Data);

void displayPixel(Console * game, SHORT x, SHORT y, WORD attrib);
void displayPixel(Console * game, COORD c, WORD attrib);

void displayPixelVector(Console * game, SHORT offsetX, SHORT offsetY, std::vector<Pixel>* Data);
void displayPixelVector(Console * game, COORD offset, std::vector<Pixel>* Data);
void displayPixelVector(Console * game, std::vector<Pixel> *Data);

#endif