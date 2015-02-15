using namespace std;

#include <iostream>
#include<stdio.h>

#include "VariableClass.h"

class C_MemMng{
private:
	const int objSum = 100;
	OBJ_LIST* wait;
	OBJ_LIST* act;

	OBJECT* RetEndPt(int qty);

public:
	C_MemMng();
	~C_MemMng();

	void GetObjectPtr(int qty, OBJ_LIST* outObj);
	void RetObjectPtr(OBJECT* ret);

	void DispCnt();
};
