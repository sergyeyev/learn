#include "pch.h"
#include <iostream>
#include "consts.h"
#include "strutils.h"
#include "tgeom.h"
#include "trect.h"
#include "consoleroutine.h"

TRect::TRect() {
	TGeom::TGeom();
	width  = 0;
	height = 0;
}

TRect::~TRect() {
	Erase();
	TGeom::~TGeom();
}

void TRect::InitTest() {
	TGeom::InitTest();
	width  = rand() % 5 + 3;
	height = rand() % 5 + 3;
};

void TRect::setBounds(const short X, const short Y, const short HEIGHT, const short WIDTH) {
	x      = X;
	y      = Y;
	height = HEIGHT;
	width  = WIDTH;
}

short TRect::getHeight() {
	return height;
};

void  TRect::setHeight(const short HEIGHT) {
	if (HEIGHT != height) {
		Erase();
		height = HEIGHT;
	}
  
};

short  TRect::getWidth() {
	return width;
};

void  TRect::setWidth(const short WIDTH) {
	if (WIDTH != width) {
		Erase();
		width = WIDTH;
	}
};


int TRect::Contains(const short X, const short Y) {
	int result = 0;
	if ( (X >= getX() ) && (Y >= getY()) && (X <= (getX() + width)) && (Y <= (getY() +height)) ) {
		result = 1;
	}
	return result;
}

void TRect::Print() {
	consoleSetColors( getColor(), getBgColor() );
	for (int i = getX(); i < (getX() + width); i++) {
		for (int j = getY(); j < (getY() + height); j++) {
			consoleGotoXY(i, j);
			printf("%c", getSymb());
		}
	}
}

void TRect::Erase() {
	consoleSetColors(clBlack, clBlack);
	for (int i = getX(); i < (getX() + width); i++) {
		for (int j = getY(); j < (getY() + height); j++) {
			consoleGotoXY(i, j);
			printf(" ");
		}
	}
}

void TRect::SaveToFile(FILE *fileHandle) {
	fprintf_s(fileHandle, "TRECT|%d|%d|%d|%d|%d|%d|%d|%c|%s\n", id, getX(), getY(), width, height, (int)getColor(), (int)getBgColor(), getSymb(), name);
}


int TRect::LoadFromStr(char *buffer) {
	int result = 0;
	char *p_block = (char *)malloc(defaultNameLength * sizeof(char));
	char *parser = buffer;
	parser = parseItem(parser, '|', p_block);
	parser = parseItem(parser, '|', p_block); id = atoi(p_block);
	parser = parseItem(parser, '|', p_block); x = atoi(p_block);
	parser = parseItem(parser, '|', p_block); y = atoi(p_block);
	parser = parseItem(parser, '|', p_block); width = atoi(p_block);
	parser = parseItem(parser, '|', p_block); height = atoi(p_block);
	parser = parseItem(parser, '|', p_block); color = (ConsoleColors)atoi(p_block);
	parser = parseItem(parser, '|', p_block); bgcolor = (ConsoleColors)atoi(p_block);
	parser = parseItem(parser, '|', p_block); symb = *p_block;
	parser = parseItem(parser, '\n', p_block);
	strcpy_s(name, strlen(p_block) + 1, p_block);
	free(p_block);
	return result;
}