#pragma once

//Point
inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };

	return pt;
}

//Line
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

//Rect
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };

	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };

	return rc;
}

//Rectangle
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width /2), y - (height / 2), x + (width / 2), y + (height / 2));
}

inline void RectangleRECT(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//Ellipse
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

inline void EllipseRECT(HDC hdc, RECT rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

inline RECT getRect(int x, int y, int width, int height)
{
	RECT rc;
	rc.left = x - width / 2;
	rc.right = x + width / 2;
	rc.top = y - width / 2;
	rc.bottom = y + width / 2;
	return rc;
}