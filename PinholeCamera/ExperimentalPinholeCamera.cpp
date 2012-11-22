#include "ExperimentalPinholeCamera.h"

#include <cstdio>
#include <iostream>
#include <opencv2/calib3d/calib3d.hpp>

using namespace cv;



using namespace std;

namespace pinholeCamera{

ExperimentalPinholeCamera::ExperimentalPinholeCamera(Mat K, Mat RT)
{
	this->K = K;
	this->RT = RT;

	this->T = RT(Range::all(), Range(3,4));
	this->R = RT(Range(0,3), Range(0,3));


}

ExperimentalPinholeCamera::ExperimentalPinholeCamera(float d, Point center, Mat rotationVector, Mat translation)
{
	this->K = Mat::eye(4,4, CV_32FC1);
	this->K.at<float>(3,3) = 0;
	
	this->RT = Mat::eye(4,4, CV_32FC1);
	
	this->T = RT(Range::all(), Range(3,4));
	this->R = RT(Range(0,3), Range(0,3));

	Rodrigues(rotationVector, this->R);

	//this->R.at<float>(0,1) *= -1;
	//this->R.at<float>(1,1) *= -1;
	//this->R.at<float>(2,1) *= -1;	
	
	for(int i = 0; i < 3; i++ ) this->T.at<float>(i) = translation.at<float>(i);


	this->setProjectionCenter(center);
	this->setProjectionDepth(d);

	cout << this->RT << endl;

}

void ExperimentalPinholeCamera::setRT(const Mat& RT)
{
	this->RT = RT;

	this->T = RT(Range::all(), Range(3,4)); 
}


void ExperimentalPinholeCamera::transform(pinholeCamera::Model& model)
{
	Mat worldModelMatrix(model.points.size(),1, CV_32FC3);

	Point3f p;

	for(int i = 0; i < model.points.size(); i++)
	{
		p = model.getTransformedPoint(i);

		worldModelMatrix.at<Vec3f>(i)[0] = p.x;
		worldModelMatrix.at<Vec3f>(i)[1] = p.y;
		worldModelMatrix.at<Vec3f>(i)[2] = p.z;
	}

	
	Mat viewModelMatrix;
	Mat projectedModelMatrix;
	//Mat P = K*RT;
		
	perspectiveTransform(worldModelMatrix, viewModelMatrix, RT );
	perspectiveTransform(viewModelMatrix, projectedModelMatrix, K );

	//model.pixels.resize(model.points.size());
	model.pixels.clear();

	for(int i = 0; i < projectedModelMatrix.rows; i++)
	{
		//if( (viewModelMatrix.at<Vec3f>(i)[2] - (this->T.at<float>(2) + d)) < 0 || (viewModelMatrix.at<Vec3f>(i)[2] - this->T.at<float>(2)) < 0 )
			//continue;

		model.pixels.push_back(Pixel(projectedModelMatrix.at<Vec3f>(i)[0],projectedModelMatrix.at<Vec3f>(i)[1]));
	}

}

void ExperimentalPinholeCamera::setProjectionCenter( Point center )
{
	this->center = center;

	this->K.at<float>(0,2) = this->center.x/this->d;
	this->K.at<float>(1,2) = this->center.y/this->d;
}

void ExperimentalPinholeCamera::setProjectionDepth(float d)
{
	this->d = d;

	this->K.at<float>(3,2) = 1.0f/this->d;
	this->K.at<float>(0,2) = this->center.x/this->d;
	this->K.at<float>(1,2) = this->center.y/this->d;
}

void ExperimentalPinholeCamera::rotateCamera( float rx, float ry, float rz)
{

	Rodrigues( Mat(Point3f(rx,ry,rz)), this->R);

}

void ExperimentalPinholeCamera::translateCamera( float x, float y, float z)
{
	this->T.at<float>(0) = x;
	this->T.at<float>(1) = y;
	this->T.at<float>(2) = z;
}


}