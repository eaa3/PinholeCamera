#pragma once
#include "Model.h"
#include <utility>

namespace pinholeCamera{

class Polygon :
	public Model
{
public:
	vector< pair<int,int> > edges;
	int granularity;


	Polygon( string fileName, int granularity );
	virtual ~Polygon(void);


	virtual void loadFromFile( string fileName );



};

}

