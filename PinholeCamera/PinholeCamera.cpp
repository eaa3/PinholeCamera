#include "PinholeCamera.h"

namespace pinholeCamera{

PinholeCamera::PinholeCamera(Vec3f rvector, Vec3f translation)
{
	Rodrigues(rvector,this->R);
	this->T = Mat(translation);

	this->r = -1;
	this->l = 1;
	this->b = -1;
	this->t = 1;

	this->n = 1;
	this->f = 2;

	this->setFrustum(l,r,b,t,n,f);

	cout << "olha1\n " << this->R << endl;
	cout << this->T << endl;
}


PinholeCamera::~PinholeCamera(void)
{
}


void PinholeCamera::loadRotationMatrix(Vec3f rvector)
{
	Rodrigues(rvector, this->R);
}

void PinholeCamera::loadRotationMatrix(Mat& R)
{
	this->R = R;
}

void PinholeCamera::loadTranslation(Vec3f translation)
{
	this->T = Mat(translation);
}
void PinholeCamera::loadTranslation(Mat& translation)
{
	this->T = translation;
}

void PinholeCamera::setFrustum(float l, float r, float b, float t, float n, float f)
{
	float A, B, X, Y, C, D;

	X = 2*n/(r-l);
	Y = 2*n/(t-b);
	C = (-r-l)/(r-l);
	D = (-t-b)/(t-b);
	A = (-f-n)/(n-f);
	B = 2*f*n/(n-f);

	float k[] = { X, 0, C, 0,
				 0, Y, D, 0,
				 0, 0, A, B,
				 0, 0, 1, 0};
	Mat temp = Mat(4,4, CV_32FC1, k);
	
	this->K = Mat::eye(4,4, CV_32FC1);
	temp.copyTo(this->K);

}

void PinholeCamera::transform(Model& model, vector<Mat> & transformedPoints )
{
	Mat RT = this->getRT();

	Mat P = K*RT;

	transformedPoints.resize(model.points.size());

	Mat point;
	for(int i = 0; i < model.points.size(); i++)
	{
		point = Mat(model.getTransformedPoint(i));
		point.resize(4,1);


		transformedPoints[i] = P*point;
	
	}


	

}

Mat PinholeCamera::getRT()
{

	Mat RT = Mat::eye(4,4, CV_32FC1); //Extrinsic matrix

	Mat RT_r = RT(Range(0,3),Range(0,3)); //Sub matrix: rotation part
	Mat RT_t = RT(Range(0,3), Range(3,4)); //Sub matrix: translation part
	
	//Copying data to RT
	this->R.copyTo(RT_r);

	Mat t = -this->R*this->T;

	t.copyTo(RT_t);

	return RT;
}

}