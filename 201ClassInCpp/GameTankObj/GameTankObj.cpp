#include "pch.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <locale.h>
#include "../ClassInCpp/consts.h"
#include "../ClassInCpp/strutils.h"
#include "../ClassInCpp/consoleroutine.h"
#include "../ClassInCpp/tgeom.h"
#include "../ClassInCpp/tpoint.h"
#include "../ClassInCpp/trect.h"
#include "../ClassInCpp/tcircle.h"
#include "../ClassInCpp/list2link.h"
#include "../ClassInCpp/gameengine.h"

int main() {
	GameEngine *Game = new GameEngine();

	Game->Run();

	delete Game;

	return 0;
}