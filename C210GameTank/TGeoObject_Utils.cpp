#include <iostream>
#include "StringHelper.h"
#include "TGeoObject.h"
#include "TGeoObjectBank.h"
#include "TGeoObjectHouse.h"
#include "TGeoObjectShop.h"
#include "TGeoObjectTank.h"

TGeoObject* LoadFromFile(const char* FileName) {
	TGeoObject* LResult = NULL;
	FILE* LFileHandle;
	int LFileOpenError = fopen_s(&LFileHandle, FileName, "r");
	if (0 == LFileOpenError) {
		char* LClassName = StringHelper::New();
		char* LBuffer = StringHelper::New(StringHelper::DefaultBufferSize);
		char* LWork = LBuffer;
		while (!feof(LFileHandle)) {
			*LWork = fgetc(LFileHandle);
			if ('\n' == *LWork) {
				*LWork = '|';
				StringHelper::Parse(LBuffer, '|', LClassName);
				if (0 == strcmp(LClassName, "TGEOOBJECTHOUSE")) {
					if (NULL == LResult) {
						LResult = new TGeoObjectHouse();
					}
					else {
						LResult = LResult->ListAdd(new TGeoObjectHouse());
					}
				}
				else if (0 == strcmp(LClassName, "TGEOOBJECTSHOP")) {
					if (NULL == LResult) {
						LResult = new TGeoObjectShop();
					}
					else {
						LResult = LResult->ListAdd(new TGeoObjectShop());
					}
				}
				else if (0 == strcmp(LClassName, "TGEOOBJECTBANK")) {
					if (NULL == LResult) {
						LResult = new TGeoObjectBank();
					}
					else {
						LResult = LResult->ListAdd(new TGeoObjectBank());
					}
				}
				if (NULL != LResult) {
					LResult->LoadFromString(LBuffer);
				}
				StringHelper::Null(LBuffer, StringHelper::DefaultBufferSize);
				LWork = LBuffer;
			}
			else {
				LWork++;
			}
		}
		free(LBuffer);
		free(LClassName);
		fclose(LFileHandle);
	}
	return LResult;
}