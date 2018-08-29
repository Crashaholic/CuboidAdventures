#pragma once
#ifndef CONSOLEHEAD
#define CONSOLEHEAD
#include <windows.h>
#include <string>

bool isKeyPressed(unsigned short key);

class Console 
{
	public:
		Console(SHORT w, SHORT h, LPCSTR title);
		~Console();
	
		COORD realsize() { return cConsoleSize; };
		COORD size() { return { cConsoleSize.X >> 1, cConsoleSize.Y }; };
		void changeFont(SHORT width, SHORT height, LPCWSTR fontName);
		void writeToBuffer(SHORT x, SHORT y, LPCSTR str, WORD attrib = 0x0f);
		void writeToBuffer(SHORT x, SHORT y, char ch, WORD attrib = 0x0f);
		void writeToBuffer(SHORT x, SHORT y, std::string &str, WORD attrib = 0x0f);
		void writeToBuffer(COORD c, LPCSTR str, WORD attrib = 0x0f);
		void writeToBuffer(COORD c, char ch, WORD attrib = 0x0f);
		void writeToBuffer(COORD c, std::string &str, WORD attrib = 0x0f);
		void clearBuffer(WORD attrib = 0x0f);
		void bufferToConsole();

	private:
		HANDLE hConsole;
		const UINT32 buffSize;
		CHAR_INFO* ciBuffer;
		COORD cConsoleSize;
		DWORD previousMode;

		void initConsole(SHORT width, SHORT height, LPCSTR title = 0);
		void writeToConsole(const CHAR_INFO* buffer);
		void shutdownProcedure();
};
#endif