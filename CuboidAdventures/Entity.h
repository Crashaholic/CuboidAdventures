#pragma once
#include <windows.h>

class Entity 
{
public: 
	COORD pos() { return position; };

private:
	COORD position;
};