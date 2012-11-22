#pragma once

#include <opencv2/core/core.hpp>

using namespace cv;

namespace pinholeCamera{

class Pixel :
	public Point3f
{
public:
	Pixel(void);
	Pixel(float x, float y) : Point3f(x,y, 0){ }
	Pixel(float x, float y, float z) : Point3f(x,y, z){ }
	
	virtual ~Pixel(void);



	Scalar color;
};

}
