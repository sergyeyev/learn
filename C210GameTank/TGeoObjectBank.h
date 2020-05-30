#ifndef TGEOOBJECTBANK_H
#define TGEOOBJECTBANK_H

#include "TGeoObject.h"

class TGeoObjectBank : public TGeoObject {
public:
	int BankCount;
	int TermCount;
	TGeoObjectBank();
	virtual void GenTest();
	virtual void Print();
	virtual void Save(FILE* FileHandle);
	virtual char* LoadFromString(char* Text);
};

#endif
