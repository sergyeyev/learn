#ifndef TGEOOBJECTSHOP_H
#define TGEOOBJECTSHOP_H

#include "TGeoObject.h"

class TGeoObjectShop : public TGeoObject {
public:
	double Square;
	TGeoObjectShop();
	virtual void GenTest();
	virtual void Print();
	virtual void Save(FILE* FileHandle);
};

#endif
