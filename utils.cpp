#include "stdafx.h"
#include "utils.h"

namespace frameWork //<--��� ���ϴ´��
{
	//�Ÿ� �������� �Լ�
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}

	//���� �������� �Լ�
	float getAngle(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		//float distance = sqrtf(x * x + y * y);
		//float angle = acosf(x / distance);

		//if (y > 0) angle = PI2 - angle;
		float angle = atan(y / x) + PI / 2;
		if (x < 0) angle += PI;

		return angle;
	}
	
	void setMoveAngle(float angle, float size, float* x, float* y)
	{
		*x += size * sin(angle);
		*y += size * -cos(angle);
	}
}