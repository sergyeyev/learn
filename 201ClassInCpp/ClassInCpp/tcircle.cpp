#include "pch.h"
#include <iostream>
#include "consts.h"
#include "strutils.h"
#include "tgeom.h"
#include "tcircle.h"
#include "consoleroutine.h"

TCircle::TCircle() {
	TGeom::TGeom();
	r = 0;
}

TCircle::~TCircle() {
	Erase();
	TGeom::~TGeom();
}

short TCircle::getR() {
	return r;
};

void TCircle::setR(const short R) {
	if (R != r) {
		Erase();
		r = R;
	}
};


void TCircle::InitTest() {
	TGeom::InitTest();
	r = rand() % 4 + 3;
};

int TCircle::Contains(const short X, const short Y){
	int result = 0;
	if ( ( (X - getX() )*(X - getX()) + (Y - getY())*(Y - getY()) ) <= (r * r) ) {
		result = 1;
	}
	return result;
};

void TCircle::Print() {
	consoleSetColors( getColor(), getBgColor() );
	for (int i = (getX() - r); i <= (getX() + r); i++) {
		for (int j = (getY() - r); j <= (getY() + r); j++) {
			if ( 1 == Contains(i, j) ) {
				consoleGotoXY(i, j);
				printf("%c", getSymb() );
			}
		}
	}
}

void TCircle::Erase() {
	consoleSetColors(clBlack, clBlack);
	for (int i = (getX() - r); i <= (getX() + r); i++) {
		for (int j = (getY() - r); j <= (getY() + r); j++) {
			if (1 == Contains(i, j)) {
				consoleGotoXY(i, j);
				printf(" ");
			}
		}
	}
}

void TCircle::SaveToFile(FILE *fileHandle) {
   fprintf_s(fileHandle, "TCIRC|%d|%d|%d|%d|%d|%d|%c|%s\n", id, getX(), getY(), r, (int)getColor(), (int)getBgColor(), getSymb(), name);
}

int TCircle::LoadFromStr(char *buffer) {
	int result = 0;
	char *p_block = (char *)malloc(defaultNameLength * sizeof(char));
	char *parser = buffer;
	parser = parseItem(parser, '|', p_block);
	parser = parseItem(parser, '|', p_block); id = atoi(p_block);
	parser = parseItem(parser, '|', p_block); x = atoi(p_block);
	parser = parseItem(parser, '|', p_block); y = atoi(p_block);
	parser = parseItem(parser, '|', p_block); r = atoi(p_block);
	parser = parseItem(parser, '|', p_block); color = (ConsoleColors)atoi(p_block);
	parser = parseItem(parser, '|', p_block); bgcolor = (ConsoleColors)atoi(p_block);
	parser = parseItem(parser, '|', p_block); symb = *p_block;
	parser = parseItem(parser, '\n', p_block); strcpy_s(name, strlen(p_block) + 1, p_block);
	free(p_block);
	return result;
}
