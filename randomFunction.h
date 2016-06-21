#pragma once
#include "singletonBase.h"
#include <time.h>

//=====================================
// ## randomFunction ##
//=====================================

class randomFunction : public singletonBase < randomFunction >
{
public:
	randomFunction(void)
	{
		srand(GetTickCount());
	}
	~randomFunction(void)
	{
	}

	//int�� ������ ��������
	inline int getInt(int num) { return rand() % num; }
	inline int getFromIntTo(int fromNum, int toNum) { return rand() % (toNum - fromNum + 1) + fromNum; }

	//float�� ������ ��������
	inline float getFloat() { return (float)rand() / (float)RAND_MAX; }
	inline float getFloat(float num) { return ((float)rand() / (float)RAND_MAX) * num; }
	inline float getFromFloatTo(float fromFloat, float toFloat)
	{
		float rnd = (float)rand() / (float)RAND_MAX;

		return (rnd * (toFloat - fromFloat) + fromFloat);
	}


};