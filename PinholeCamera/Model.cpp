#include "Model.h"

namespace pinholeCamera{


Model::Model( string fileName )
{
	this->loadFromFile(fileName);
	this->rx = this->ry = this->rz = 0;
}
Model::Model()
{
}

Model::~Model()
{
}

void Model::loadFromFile( string fileName )
{
	FILE* file = fopen(fileName.c_str(), "r");
	
	int npoints;
	float x,y,z;

	fscanf(file, "%d", &npoints);


	for(int i = 0; i < npoints; i++)
	{
		fscanf(file, "%f %f %f", &x, &y, &z);

		this->points.push_back( Point3f(x,y,z) );
	}

	fclose(file);
}

Point3f Model::getTransformedPoint(int i)
{
	Mat point(this->points[i]);
	
	float rotm [] = {rx,  ry,  rz };
	Mat rotationVector(3,1, CV_32FC1, rotm);

	Mat rotationMatrix;

	Rodrigues(rotationVector, rotationMatrix);

	Mat r = rotationMatrix*point;

	Point3f result(r.at<float>(0),r.at<float>(1), r.at<float>(2));

	return result + this->translation;
}

void Model::getLine(vector<Point3f>& line, int i, int j, int granularity)
{
	Point3f vdir = (this->points[j] - this->points[i])*(1.0f/granularity);

	line.resize(granularity);

	for(int k = 0; k < granularity; k++)
	{
		line[k] = this->points[i] + k*vdir;
	}


}
		
}


