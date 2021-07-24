//!! 14 b
#include "stdafx.h" // must be 1st
#include "LinedSquare.h"

//!! 22 b
IMPLEMENT_SERIAL(linedSquare, CObject, 1)
//!! 22 e

linedSquare::linedSquare(CPoint p1, CPoint p2)
	:RectangleF(p1, p2)
{
}

void linedSquare::Draw(CDC* dc) const
{

	CPoint p1 = getP1();
	CPoint p2 = getP2();
	
	dc->Rectangle(p1.x, p1.y, p2.x, p2.y);


	CPen myPen1(PS_SOLID, 1, RGB(255, 0, 0)); // Inside Line Color
	CPen* oldPen;
	oldPen = dc->SelectObject(&myPen1);
	dc->SetROP2(R2_NOTXORPEN);
	dc->MoveTo(p1);
	dc->LineTo(p2.x, p2.y);
	dc->SelectObject(oldPen);
	dc->SetROP2(R2_COPYPEN);

}

//!! 14 e
