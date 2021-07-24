#pragma once
#pragma once
#include "RectangleF.h"
#include "Figure.h"

class MagenDavid : public RectangleF {

	DECLARE_SERIAL(MagenDavid)   //!!! NO ";"  

public:

	// must 4 serialization
	MagenDavid() {}


	MagenDavid(CPoint p1, CPoint p2);
	void Draw(CDC* dc) const;
};

