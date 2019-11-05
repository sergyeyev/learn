#ifndef TPOINT_H
#define TPOINT_H

#include "tgeom.h"

enum TPointType {
	 ptUnknown = 0
	,ptBank    = 1
	,ptHouse   = 2
	,ptCafe    = 3
	,ptShop    = 4
	,ptTank    = 5
	,ptPen     = 6
};

class TPoint :public TGeom {
private:
public:
	TPoint();
	virtual TPointType getTyp();
	virtual void setTyp(const TPointType TYP);
	virtual char getSymb();
	virtual void SaveToFile(FILE *fileHandle);
	virtual int LoadFromStr(char *buffer);
protected:
	TPointType typ;
};

#endif
