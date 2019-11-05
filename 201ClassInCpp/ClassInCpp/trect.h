#ifndef TRECT_H
#define TRECT_H

#include "tgeom.h"

class TRect :public TGeom {
private:
public:
	TRect();
	virtual ~TRect();
	virtual short getHeight();
	virtual void setHeight(const short HEIGHT);
	virtual short getWidth();
	virtual void setWidth(const short WIDTH);
	virtual void setBounds(const short X, const short Y, const short HEIGHT, const short WIDTH);
	virtual void InitTest();
	virtual int Contains(const short X, const short Y);
	virtual void Print();
	virtual void Erase();
	virtual void SaveToFile(FILE *fileHandle);
	virtual int LoadFromStr(char *buffer);
protected:
	short height;
	short width;
};

#endif