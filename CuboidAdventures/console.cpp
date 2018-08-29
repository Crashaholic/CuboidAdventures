#include "console.h"

Console::Console(SHORT w, SHORT h, LPCSTR title) : buffSize(w * h)
{
	initConsole(w, h, title);
}

Console::~Console()
{
	shutdownProcedure();
}

void Console::initConsole(SHORT width, SHORT height, LPCSTR title)
{
	SMALL_RECT consoleArea = { 0, 0, width - 1, height - 1 };
	COORD buffArea = { width, height };
	DWORD previous;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle(TEXT(title));
	SetConsoleWindowInfo(hConsole, TRUE, &consoleArea);
	SetConsoleScreenBufferSize(hConsole, buffArea);
	SetConsoleWindowInfo(hConsole, TRUE, &consoleArea);
	GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &previous);
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	ciBuffer = new CHAR_INFO[buffSize];
	this->previousMode = previous;
	this->cConsoleSize = { width, height };
}

void Console::changeFont(SHORT width, SHORT height, LPCWSTR fontName)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof cfi;
	cfi.nFont = 0;
	cfi.dwFontSize.X = width;
	cfi.dwFontSize.Y = height;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, fontName);
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void Console::clearBuffer(WORD attrib)
{
	for (size_t i = 0; i < buffSize; i++)
	{
		ciBuffer[i].Char.AsciiChar = ' ';
		ciBuffer[i].Attributes = attrib;
	}
}

void Console::bufferToConsole()
{
	writeToConsole(ciBuffer);
}

void Console::writeToBuffer(SHORT x, SHORT y, LPCSTR str, WORD attrib)
{
	size_t index = max(x + cConsoleSize.X * y, 0);
	size_t length = strlen(str);
	length = min(buffSize - index, length);
	for (unsigned long long i = 0; i < length; i++)
	{
		ciBuffer[index + i].Char.AsciiChar = str[i];
		ciBuffer[index + i].Attributes = attrib;
	}
}

void Console::writeToBuffer(SHORT x, SHORT y, char ch, WORD attrib)
{
	if (x < 0 || x >= cConsoleSize.X || y < 0 || y >= cConsoleSize.Y) return;
	ciBuffer[x + cConsoleSize.X * y].Char.AsciiChar = ch;
	ciBuffer[x + cConsoleSize.X * y].Attributes = attrib;
}

void Console::writeToBuffer(SHORT x, SHORT y, std::string &str, WORD attrib)
{
	writeToBuffer(x, y, str.c_str(), attrib);
}

void Console::writeToBuffer(COORD c, LPCSTR str, WORD attrib)
{
	writeToBuffer(c.X, c.Y, str, attrib);
}

void Console::writeToBuffer(COORD c, char ch, WORD attrib)
{
	writeToBuffer(c.X, c.Y, ch, attrib);
}

void Console::writeToBuffer(COORD c, std::string &str, WORD attrib)
{
	writeToBuffer(c.X, c.Y, str.c_str(), attrib);
}

void Console::writeToConsole(const CHAR_INFO* buffer)
{
	COORD c = { 0,0 };
	SMALL_RECT writeArea = { 0, 0, cConsoleSize.X - 1, cConsoleSize.Y - 1 };
	WriteConsoleOutputA(hConsole, buffer, cConsoleSize, c, &writeArea);
}

void Console::shutdownProcedure()
{
	delete[] ciBuffer;
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), previousMode);
	SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
}

bool isKeyPressed(unsigned short key)
{
	return ((GetAsyncKeyState(key) & 0x8001) != 0);
}