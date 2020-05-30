#ifndef TGEOOBJECTTANK_H
#define TGEOOBJECTTANK_H

#include "TGeoObject.h"

class TGeoObjectTank: public TGeoObject {
public:
	TGeoObjectTank();
	virtual void Draw();
};

#endif