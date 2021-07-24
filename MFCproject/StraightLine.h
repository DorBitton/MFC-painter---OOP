#pragma once
#include "RectangleF.h"

class StraightLine : public RectangleF {

	DECLARE_SERIAL(StraightLine)   //!!! NO ";"  

public:

	// must 4 serialization
	StraightLine() {}


	StraightLine(CPoint p1, CPoint p2);
	void Draw(CDC* dc) const;
};

