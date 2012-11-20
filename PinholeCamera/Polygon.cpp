#include "Polygon.h"

namespace pinholeCamera{

Polygon::Polygon( string fileName, int granularity )
{

	this->granularity = granularity;

	this->loadFromFile(fileName);
}


Polygon::~Polygon(void)
{
}


void Polygon::loadFromFile( string fileName )
{
	FILE* file = fopen(fileName.c_str(), "r");
	
	int npoints, nedges;
	float x,y,z;
	int first, second;
	vector< Point3f > line;


	fscanf(file, "%d", &npoints);

	this->points.resize(npoints);
	for(int i = 0; i < npoints; i++)
	{
		fscanf(file, "%f %f %f", &this->points[i].x, &this->points[i].y, &this->points[i].z);
	}

	fscanf(file, "%d", &nedges);

	this->edges.resize(nedges);

	for(int i = 0; i < nedges; i++)
	{
		fscanf(file, "%d %d", &this->edges[i].first, &this->edges[i].second);

		this->getLine(line, this->edges[i].first, this->edges[i].second, this->granularity);

		this->points.insert(this->points.end(), line.begin(), line.end() );
	}



	fclose(file);

}

}