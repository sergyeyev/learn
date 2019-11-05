#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include "consts.h"
#include "strutils.h"
#include "tgeom.h"
#include "consoleroutine.h"

TGeom::TGeom() {
	x       = 0;
	y       = 0;
	symb    = ' ';
	name    = (char *)malloc( defaultNameLength * sizeof(char) );
	color   = clBlack;
	bgcolor = clBlack;
}

TGeom::~TGeom() {
	Erase();
//	free(name);
}

int TGeom::getX() {
	return x;
};

void TGeom::setX(const int X) {
	if (X != x) {
		Erase();
		x = X;
	}
};

int TGeom::getY() {
	return y;
};

void TGeom::setY(const int Y) {
	if (Y != y) {
		Erase();
		y = Y;
	}
};

char TGeom::getSymb() {
	return symb;
};

void TGeom::setSymb(const char SYMB) {
	if (SYMB != symb) {
		Erase();
		symb = SYMB;
	}
};

ConsoleColors TGeom::getColor() {
	return color;
};

void TGeom::setColor(const ConsoleColors COLOR) {
	if (COLOR != color) {
		Erase();
		color = COLOR;
	}
};

ConsoleColors TGeom::getBgColor() {
	return bgcolor;
};

void TGeom::setBgColor(const ConsoleColors BGCOLOR) {
	if (BGCOLOR != bgcolor) {
		Erase();
		bgcolor = BGCOLOR;
	}
};

void TGeom::InitTest() {
	x = rand() % consoleSizeX() + 1;
	y = rand() % consoleSizeY() + 1;
	symb = '?';
	color   = (ConsoleColors)(rand() % 16);
	bgcolor = color;
	int namelen = rand() % defaultNameLength + 1;
	char *n = name;
	for (int k = 0; k < namelen - 1; k++) {
		*n = (char)(rand() % 26 + 65);
		n++;
	}
	*n = 0;
};

void TGeom::Print() {
	consoleSetColors( getColor(), getBgColor() );
	consoleGotoXY( getX(), getY() );
	printf("%c", getSymb() );
}

void TGeom::PrintText() {
	consoleSetColors(getBgColor(), clBlack);
	printf("  %d [%3d:%3d] %s\n", id, x, y, name);
}


void TGeom::Erase() {
	consoleSetColors(clBlack, clBlack);
	consoleGotoXY(getX(), getY());
	printf(" ");
}

int TGeom::Contains(const short X, const short Y){
	int result = 0;
	if ( (x == X) && (y == Y) ) {
		result = 1;
	}
	return result;
}

void TGeom::SaveToFile(FILE *fileHandle) {
	fprintf_s(fileHandle, "TGEOM|%d|%d|%d|%d|%d|%c|%s\n", id, x, y, (int)color, (int)bgcolor, getSymb(), name);
}

int TGeom::LoadFromStr(char *buffer) {
	int result = 0;
	char *p_block = (char *)malloc(defaultNameLength * sizeof(char));
	char *parser = buffer;
	parser = parseItem(parser, '|', p_block);
	parser = parseItem(parser, '|', p_block); id      = atoi(p_block);
	parser = parseItem(parser, '|', p_block); x       = atoi(p_block);
	parser = parseItem(parser, '|', p_block); y       = atoi(p_block);
	parser = parseItem(parser, '|', p_block); color   = (ConsoleColors)atoi(p_block);
	parser = parseItem(parser, '|', p_block); bgcolor = (ConsoleColors)atoi(p_block);
	parser = parseItem(parser, '|', p_block); symb    = *p_block;
	parser = parseItem(parser, '\n', p_block); strcpy_s(name, strlen(p_block)+1, p_block);
	free(p_block);
	return result;
}
