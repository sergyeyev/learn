#ifndef APPLICATIONGLOBALS_H
#define APPLICATIONGLOBALS_H

#include <iostream>
#include "../data/DataItem.h"
#include "../data/DataGoods.h"
#include "../data/DataWarrior.h"


extern char* GAppDefaultDocPath;
extern char* GAppDefaultFileWarrior;
extern char* GAppDefaultFileGoods;

// глобальные перемнные для модели данных
extern Warrior* GWarriors;
extern Good* GGoods;


#endif