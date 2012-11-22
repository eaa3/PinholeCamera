#ifndef _PINHOLE_CAMERA_
#define _PINHOLE_CAMERA_

#include <opencv2/core/core.hpp>
#include "Pixel.h"
#include "Model.h"

using namespace cv;


const float PI = 3.14159265359;

namespace pinholeCamera{

class ExperimentalPinholeCamera
{
public:
	
	//Intrinsic params
	Mat K;
	//Extrinsic params
	Mat RT;
	//Translation vector(ROI of RT)
	Mat T;
	//Rotation matrix(ROI of RT)
	Mat R;

	Point center; //Center of projection
	float d; //Projection depth


	ExperimentalPinholeCamera(Mat K, Mat RT);
	ExperimentalPinholeCamera::ExperimentalPinholeCamera(float d, Point center, Mat rotationVector, Mat translation);


	void transform(pinholeCamera::Model& model);


	void setRT(const Mat& RT);

	void setProjectionCenter( Point center );

	void setProjectionDepth(float d);

	void rotateCamera( float rx, float ry, float rz);
	
	void translateCamera( float x, float y, float z);


};

}



#endif