#ifndef TGEOOBJECTHOUSE_H
#define TGEOOBJECTHOUSE_H

#include "TGeoObject.h"
class TGeoObjectHouse : public TGeoObject {
public:
	int CabCount;
	TGeoObjectHouse();
	virtual void GenTest();
	virtual void Print();
	virtual void Save(FILE* FileHandle);
};

#endif
