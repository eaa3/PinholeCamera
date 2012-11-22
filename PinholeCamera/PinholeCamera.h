#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include "Model.h"
#include <vector>
#include <iostream>


using namespace std;
using namespace cv;

namespace pinholeCamera{

class PinholeCamera
{
public:
	
	//Extrinsic Params
	Mat R;
	Mat T;


	//Intrinsic params: Perspective matrix (Projection matrix)
	Mat K;

	//Frustum limits
	float n, f, r, l, b, t; //near, far, right, left bottom, top

	//Loads the camera model with a default frustum, and the following extrinsic params taken as input
	PinholeCamera(Vec3f rvector, Vec3f translation);

	~PinholeCamera(void);

	//Load a rotation Matrix from a rotation vector v = (rx, ry, rz) which indicates how much the coordinates will be rotate in each axis.
	void loadRotationMatrix(Vec3f rvector);

	//Load a rotation Matrix directly
	void loadRotationMatrix(Mat& R);

	//Load translation given as a vector or as a Mat
	void loadTranslation(Vec3f translation);
	void loadTranslation(Mat& translation);
	
	//Sets the perspective matrix (Projection Matrix) according to the following Frustum limits
	void setFrustum(float l, float r, float b, float t, float n, float f);

	void transform(Model& model, vector<Mat> & transformedPoints);


	Mat getRT();

	
};

}