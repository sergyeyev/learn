#include <Windows.h>
#include "Console.h"

HANDLE Console::GetConsoleHandle(DWORD ConsoleId) {
	return GetStdHandle(ConsoleId);
}

HANDLE Console::GetConsole() {
	return GetConsoleHandle( STD_OUTPUT_HANDLE );
}

void Console::GotoXY(const short x, const short y) {
	COORD LPos;
	LPos.X = x;
	LPos.Y = y;
	SetConsoleCursorPosition( GetConsole(), LPos );
}

void Console::GotoX(const short x) {
	GotoXY( x, Y() );
};

void Console::GotoY(const short y) {
	GotoXY( X(), y);
};


WORD Console::GetColor(const ConsoleColors Foreground, const ConsoleColors Background) {
	// 1) XXXX 0110  Background = clYellow
	// 2)            << 4
	// 3) 0110 0000
	// 4)            |
	// 5) 0000 0100  Foreground = clRed 
	// ==================================
	// 6) 0110 0100 
	return (WORD)(Background << 4) | Foreground;
}

void Console::SetColor(const ConsoleColors Foreground, const ConsoleColors Background) {
	SetConsoleTextAttribute( GetConsole(), GetColor(Foreground, Background) );
}

short Console::X() {
	short LResult = 0;
	PCONSOLE_SCREEN_BUFFER_INFO LScrInfo = (PCONSOLE_SCREEN_BUFFER_INFO)malloc(sizeof(struct _CONSOLE_SCREEN_BUFFER_INFO));
	if (TRUE == GetConsoleScreenBufferInfo( GetConsole(), LScrInfo) ) {
		LResult = LScrInfo->dwCursorPosition.X;
	}
	free(LScrInfo);
	return LResult;
};

short Console::Y() {
	short LResult = 0;
	PCONSOLE_SCREEN_BUFFER_INFO LScrInfo = (PCONSOLE_SCREEN_BUFFER_INFO)malloc(sizeof(struct _CONSOLE_SCREEN_BUFFER_INFO));
	if (TRUE == GetConsoleScreenBufferInfo(GetConsole(), LScrInfo)) {
		LResult = LScrInfo->dwCursorPosition.Y;
	}
	free(LScrInfo);
	return LResult;
};

short Console::Width() {
	short LResult = 0;
	PCONSOLE_SCREEN_BUFFER_INFO LScrInfo = (PCONSOLE_SCREEN_BUFFER_INFO)malloc(sizeof(struct _CONSOLE_SCREEN_BUFFER_INFO));
	if (TRUE == GetConsoleScreenBufferInfo(GetConsole(), LScrInfo)) {
		LResult = LScrInfo->dwSize.X;
	}
	free(LScrInfo);
	return LResult;
};

short Console::Height() {
	short LResult = 0;
	PCONSOLE_SCREEN_BUFFER_INFO LScrInfo = (PCONSOLE_SCREEN_BUFFER_INFO)malloc(sizeof(struct _CONSOLE_SCREEN_BUFFER_INFO));
	if (TRUE == GetConsoleScreenBufferInfo(GetConsole(), LScrInfo)) {
		LResult = LScrInfo->dwSize.Y;
	}
	free(LScrInfo);
	return LResult;
}

void Console::FillRect(const short X, const short Y, const short Width, const short Height, const char Symb) {
	COORD LCoord = {X, Y};
	//LCoord.X = X;
	//LCoord.Y = Y;
	DWORD LSymbolCount = Height * Width;
	DWORD LSymbolWritten = 0;
	PCONSOLE_SCREEN_BUFFER_INFO LScrInfo = (PCONSOLE_SCREEN_BUFFER_INFO)malloc(sizeof(struct _CONSOLE_SCREEN_BUFFER_INFO));
	GetConsoleScreenBufferInfo(GetConsole(), LScrInfo);
	FillConsoleOutputCharacterA(GetConsole(), Symb, LSymbolCount, LCoord, &LSymbolWritten);
	FillConsoleOutputAttribute(GetConsole(), LScrInfo->wAttributes, LSymbolCount, LCoord, &LSymbolWritten);
	free(LScrInfo);
}