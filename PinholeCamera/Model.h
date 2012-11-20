#ifndef _BASE_MODEL_
#define _BASE_MODEL_


#include <string>
#include <cstdio>
#include <opencv2/core/core.hpp>
#include "Pixel.h"
#include <opencv2/calib3d/calib3d.hpp>
#include <cmath>

using namespace std;
using namespace cv;

namespace pinholeCamera{

class Model
{
public:
	vector<Point3f> points;
	vector<Pixel> pixels;

	Point3f translation;
	float rx, ry, rz;

	Model( string fileName );
	Model();
	virtual ~Model();


	virtual void loadFromFile( string fileName );


	Point3f getTransformedPoint(int i);

	void getLine(vector<Point3f>& line, int i, int j, int granularity = 10);

	
};

}



#endif