#pragma once

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
using namespace cv;



namespace pinholeCamera{

bool pointComp(const Point3f& p1, const Point3f& p2);


class Painter
{
public:

	float x, y;
	float w,h;
	float f, n;
	

	Painter(float w, float h, float x = 0, float y = 0, float f = 1, float n = 0);



	void draw(vector<Mat>& points, Mat& screenSurface, bool clip = true);

	Point3f viewportTransform( Point3f point );



	virtual ~Painter(void);


	



};

}

