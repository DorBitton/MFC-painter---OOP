//!! 14 b
#include "stdafx.h" // must be 1st
#include "StraightLine.h"

//!! 22 b
IMPLEMENT_SERIAL(StraightLine, CObject, 1)
//!! 22 e

StraightLine::StraightLine(CPoint p1, CPoint p2)
	:RectangleF(p1, p2)
{
}

void StraightLine::Draw(CDC* dc) const
{

	CPoint p1 = getP1();
	CPoint p2 = getP2();

	dc->MoveTo(p1);
	dc->LineTo(p2.x, p2.y);



	//CPen myPen1(PS_SOLID, 1, RGB(255, 0, 0)); // Inside Line Color
	//CPen* oldPen;
	//oldPen = dc->SelectObject(&myPen1);
	//dc->SetROP2(R2_NOTXORPEN);
	//dc->SelectObject(oldPen);
	//dc->SetROP2(R2_COPYPEN);

}

//!! 14 e
