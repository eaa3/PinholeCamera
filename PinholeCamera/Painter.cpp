#include "Painter.h"

namespace pinholeCamera{


bool pointComp(const Point3f& p1, const Point3f& p2)
{
	return p1.z >  p2.z;
}

Painter::Painter(float w, float h, float x, float y,  float n, float f)
{
	this->w = w;
	this->h = h;
	this->n = n;
	this->f = f;

	this->x = x;
	this->y = y;
}

Painter::~Painter(void)
{
}


void Painter::draw(vector<Mat>& points, Mat& screenSurface, bool clip)
{
	vector<Point3f> ndcPoints;
	float xc, yc, zc, wc;
	float xn, yn, zn;

	for(int i = 0; i < points.size(); i++)
	{		
		xc = points[i].at<float>(0);
		yc = points[i].at<float>(1);
		zc = points[i].at<float>(2);
		wc = points[i].at<float>(3);

		if( clip && (fabs(xc) > fabs(wc) || fabs(yc) > fabs(wc) || fabs(zc) > fabs(wc)) )
		{
			continue;
		}

		

		xn = points[i].at<float>(0)/wc;
		yn = points[i].at<float>(1)/wc;
		zn = points[i].at<float>(2)/wc;

		ndcPoints.push_back( Point3f( xn, yn, zn ) );

		

	}

	make_heap(ndcPoints.begin(), ndcPoints.end(), pointComp);

	Scalar s[] = {Scalar(0,0,255), Scalar(0,255,0), Scalar(255,0,0) };
	int i = 0;
	while( !ndcPoints.empty() )
	{
		
		Point3f p = this->viewportTransform( ndcPoints.front() );
	
		pop_heap(ndcPoints.begin(), ndcPoints.end(), pointComp);

		ndcPoints.pop_back();


		//cout << p << endl;
		//waitKey(0);
		
		circle(screenSurface, Point(p.x, p.y) , 1, s[i], 1);

		i = (i+1)%4;


		
		
	}


}

Point3f Painter::viewportTransform( Point3f point )
{
	Point3f viewportPoint;

	viewportPoint.x = point.x*this->w/2 + (this->x + this->w/2);
	viewportPoint.y = point.y*this->h/2 + (this->y + this->h/2);
	viewportPoint.z = point.z*(this->f - this->n)/2 + (this->f + this->n)/2;


	return viewportPoint;
}




}
