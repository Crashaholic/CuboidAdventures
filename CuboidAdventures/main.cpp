#include "game.h"

int main()
{
	bool bQuitGame = false;
	init();
	while (!bQuitGame)
	{
		update();
		render();
	}
	return 0;
}