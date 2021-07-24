#pragma once
#include "RectangleF.h"

class linedSquare : public RectangleF {

	DECLARE_SERIAL(linedSquare)   //!!! NO ";"  

public:

	// must 4 serialization
	linedSquare() {}


	linedSquare(CPoint p1, CPoint p2);
	void Draw(CDC* dc) const;
};

