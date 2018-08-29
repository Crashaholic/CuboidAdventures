#include "pixel.h"

void getPixelDataFromFile(std::string fileName, std::vector<Pixel> *Data)
{
	Pixel toPushBack;
	std::string currentLine;
	std::ifstream inputfile(fileName);
	if (inputfile.is_open())
	{
		while (std::getline(inputfile, currentLine))
		{
			int x = stoi(currentLine.substr(0, currentLine.find(',')));
			toPushBack.coord.X = SHORT(x);
			int y = stoi(currentLine.substr(currentLine.find(',') + 1, currentLine.find('-') - 1));
			toPushBack.coord.Y = SHORT(y);
			std::string attribute = currentLine.substr(currentLine.find('-') + 1, currentLine.length() - currentLine.find('-'));
			std::istringstream buffer{ attribute };
			unsigned int value = 0;
			buffer >> std::hex >> value;
			toPushBack.attrib = (WORD)value;
			Data->push_back(toPushBack);
		}
		inputfile.close();
	}
}

bool pixelUnseen(Console * game, SHORT x, SHORT y)
{
	if (x < 0 || x > game->realsize().X || y < 0 || y > game->realsize().Y)
	{
		return true;
	}
	return false;
}

bool pixelUnseen(Console * game, COORD c)
{
	return pixelUnseen(game, c.X, c.Y);
}


void displayPixel(Console * game, SHORT x, SHORT y, WORD attrib)
{
	if (!pixelUnseen(game, x, y))
		game->writeToBuffer(x * 2, y, "  ", attrib);
}

void displayPixel(Console * game, COORD c, WORD attrib)
{
	displayPixel(game, c.X, c.Y, attrib);
}

void displayPixelVector(Console * game, SHORT offsetX, SHORT offsetY, std::vector<Pixel>* Data)
{
	size_t size = Data->size();
	for (size_t i = 0; i < size; i++)
	{
		displayPixel(game, (*Data)[i].coord.X + offsetX, (*Data)[i].coord.Y + offsetY, (*Data)[i].attrib);
	}
}

void displayPixelVector(Console * game, COORD offset, std::vector<Pixel>* Data)
{
	displayPixelVector(game, offset.X, offset.Y, Data);
}

void displayPixelVector(Console * game, std::vector<Pixel>* Data)
{
	displayPixelVector(game, 0, 0, Data);
}
