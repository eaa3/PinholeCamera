#pragma once

#include <opencv2/core/core.hpp>

using namespace cv;

namespace pinholeCamera{

class Pixel :
	public Point
{
public:
	Pixel(void);
	Pixel(float x, float y) : Point(x,y){ }
	
	virtual ~Pixel(void);



	Scalar color;
};

}
