#include <iostream>
#include "Console.h"
#include "TGeoObjectTank.h"

TGeoObjectTank::TGeoObjectTank() {
	Color   = Console::clBlack;
	BgColor = Console::clGreen;
	Symbol  = 'T';
}

void TGeoObjectTank::Draw() {
	TGeoObject::Draw();
	Console::GotoXY(getX(), getY());
}
