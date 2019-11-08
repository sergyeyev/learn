#ifndef CONSOLEROUTINE_H
#define CONSOLEROUTINE_H

// Определение нажатия клавиш на клавиатуре
#define KEY_ESCAPE    27  // Esc
#define KEY_SPACE     32  // пробел
#define KEY_BACKSPACE  8  // забой каретки
#define KEY_TAB        9  // Tab
#define KEY_ENTER     13  // Enter

#define KEY_UP        72
#define KEY_DOWN      80
#define KEY_LEFT      75
#define KEY_RIGHT     77

#define KEY_HOME      71
#define KEY_END       79
#define KEY_CENTER    76
#define KEY_PGUP      73
#define KEY_PGDN      81

#define KEY_INSERT    82
#define KEY_DELETE    83

#define KEY_F1        59
#define KEY_F2        60
#define KEY_F3        61
#define KEY_F4        62
#define KEY_F5        63
#define KEY_F6        64
#define KEY_F7        65
#define KEY_F8        66
#define KEY_F9        67
#define KEY_F10       68
#define KEY_F11       69
#define KEY_F12       70

enum ConsoleColors {      // LRGB LRGB    Light Reg Green Blue 
	clBlack = 0  // 0000 0000
	, clBlue = 1  // 0000 0001
	, clGreen = 2  // 0000 0010
	, clCyan = 3  // 0000 0011
	, clRed = 4  // 0000 0100
	, clMagenta = 5  // 0000 0101
	, clBrown = 6  // 0000 0110
	, clLightGrey = 7  // 0000 0111
	, clDarkGrey = 8  // 0000 1000 
	, clLightBlue = 9  // 0000 1001
	, clLightGreen = 10  // 0000 1010
	, clLightCyan = 11  // 0000 1011
	, clLightRed = 12  // 0000 1100
	, clLightMagenta = 13  // 0000 1101
	, clYellow = 14  // 0000 1110
	, clWhite = 15  // 0000 1111
};

void consoleSetColors(ConsoleColors textColor, ConsoleColors backgroundColor);
short consoleWhereX();
short consoleWhereY();
short consoleBuffSizeX();
short consoleBuffSizeY();
short consoleSizeX();
short consoleSizeY();
void consoleGotoXY(short x, short y);
void consoleGotoX(short x);
void consoleGotoY(short y);
void consoleClear();

#endif
