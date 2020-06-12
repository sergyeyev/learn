#include <iostream>
#include <Windows.h>
#include "Console.h"

HANDLE Console::GetHandle() {
	return GetStdHandle(STD_OUTPUT_HANDLE);
}

void Console::SetColor(const ConsoleColors Foreground, const ConsoleColors Background) {
	SetConsoleTextAttribute(GetHandle(), (WORD)(Background << 4) | Foreground);
}

void Console::FillRect(const char CharToFill, const short Left, const short Top, const short Height, const short Width) {
	COORD LPoint = {Left, Top};
	LPoint.X = Left;
	LPoint.Y = Top;
	DWORD LSymbolCount = Height * Width;
	DWORD LCharacterWritten = 0;
	CONSOLE_SCREEN_BUFFER_INFO LConsoleInfo;
	GetConsoleScreenBufferInfo(GetHandle(), &LConsoleInfo);
	FillConsoleOutputCharacterA(GetHandle(), CharToFill, LSymbolCount, LPoint, &LCharacterWritten);
	FillConsoleOutputAttribute(GetHandle(), LConsoleInfo.wAttributes, LSymbolCount, LPoint, &LCharacterWritten);
}

void Console::GotoXY(const short x, const short y) {
	COORD LPos;
	LPos.X = x;
	LPos.Y = y;
	SetConsoleCursorPosition(GetHandle(), LPos);
}

void Console::GotoX(const short x) {
	GotoXY(x, Y());
}

void Console::GotoY(const short y) {
	GotoXY(X(), y);
}

short Console::X() {
	short LResult = 0;
	PCONSOLE_SCREEN_BUFFER_INFO ScrInfo = (PCONSOLE_SCREEN_BUFFER_INFO)malloc(1 * sizeof(struct _CONSOLE_SCREEN_BUFFER_INFO));
	if (TRUE == GetConsoleScreenBufferInfo(GetHandle(), ScrInfo) ){
		LResult = ScrInfo->dwCursorPosition.X;
	}
	free(ScrInfo);
	return LResult;
}

short Console::Y() {
	short LResult = 0;
	PCONSOLE_SCREEN_BUFFER_INFO ScrInfo = (PCONSOLE_SCREEN_BUFFER_INFO)malloc(sizeof(struct _CONSOLE_SCREEN_BUFFER_INFO));
	if (TRUE == GetConsoleScreenBufferInfo(GetHandle(), ScrInfo) ){
		LResult = ScrInfo->dwCursorPosition.Y;
	}
	free(ScrInfo);
	return LResult;
}

short Console::Height() {
	short LResult = 0;
	PCONSOLE_SCREEN_BUFFER_INFO ScrInfo = (PCONSOLE_SCREEN_BUFFER_INFO)malloc(sizeof(struct _CONSOLE_SCREEN_BUFFER_INFO));
	if (TRUE == GetConsoleScreenBufferInfo(GetHandle(), ScrInfo)) {
		LResult = ScrInfo->dwSize.Y;
	}
	free(ScrInfo);
	return LResult;
}

short Console::Width() {
	short LResult = 0;
	_CONSOLE_SCREEN_BUFFER_INFO *ScrInfo = (_CONSOLE_SCREEN_BUFFER_INFO *)malloc(sizeof(struct _CONSOLE_SCREEN_BUFFER_INFO));
	if (TRUE == GetConsoleScreenBufferInfo(GetHandle(), ScrInfo)) {
		LResult = ScrInfo->dwSize.X;
	}
	free(ScrInfo);
	return LResult;
}

void  Console::SetScreen(const short Width, const short Height) {
	PSMALL_RECT LConsRect = (PSMALL_RECT)malloc(sizeof(_SMALL_RECT));
	LConsRect->Left   = 0;
	LConsRect->Top    = 0;
	LConsRect->Right  = Width-1;
	LConsRect->Bottom = Height-1;
	SetConsoleWindowInfo(GetHandle(), TRUE, LConsRect);
	free(LConsRect);
	
	COORD LConsoleSize;
	LConsoleSize.X = Width;
	LConsoleSize.Y = Height;
	SetConsoleScreenBufferSize(GetHandle(), LConsoleSize);
	// грязный хак
	DWORD LConsoleWindowStyle = 0;
	HWND LConsoleWindow = GetConsoleWindow();
	LConsoleWindowStyle = GetWindowLongA(LConsoleWindow, GWL_STYLE);
	LConsoleWindowStyle &= ~(WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU);
	SetWindowLongA(LConsoleWindow, GWL_STYLE, LConsoleWindowStyle);
}