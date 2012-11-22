#include <cstdlib>
#include <cstdio>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "ExperimentalPinholeCamera.h"
#include "PinholeCamera.h"
#include <opencv2/calib3d/calib3d.hpp>
#include "Polygon.h"
#include "Painter.h"


using namespace cv;
using namespace std;


int d = 50;

float K[] = { 1, 0, 340.0f/d, 0,
					  0, 1, 240.0f/d, 0,
	                  0, 0, 1, 0,
					  0, 0, 1.0f/d, 0};

float RT[] = {1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, -100,
	0, 0, 0, 1};



int main(int argc, char** argv)
{
	namedWindow("Pinhole Camera");
	namedWindow("Control Window", CV_WINDOW_NORMAL);

	int rx = 0, ry = 0, rz = 0;
	int crx = 0, cry = 0, crz = 0;
	int tx = 300, ty = 300, tz = 300;

	pinholeCamera::Pixel pixel(10,20);

	cout << pixel << endl;

	


	

	pinholeCamera::Polygon cube("cubeModel.txt", 30);
	pinholeCamera::Model model2("cubeModel.txt");

	Mat frame(Size(640,480), CV_8UC3);

	Mat k(4,4,CV_32FC1,K);
	Mat rt(4,4, CV_32FC1, RT);

	
	//c.center.x = 340.0f;
	//c.center.y = 240.0f;
	pinholeCamera::ExperimentalPinholeCamera c(d, Point(0, 0), Mat(Point3f(0,0,0)), Mat(Point3f(0,0,-100)));
	
	
	pinholeCamera::PinholeCamera c2(Vec3f(0,0,0), Vec3f(0,0,-100));
	
	c2.setFrustum(-100, 100, -100, 100, d, 400);

	pinholeCamera::Painter painter(640,480,5,100);

	vector<Mat> transformedPoints;




	while(waitKey(10) < 0){

		frame.release();

		frame = Mat(Size(640,480), CV_8UC3);


		cube.rx = rx*PI/180;
		cube.ry = ry*PI/180;
		cube.rz = rz*PI/180;

		c2.setFrustum(-100, 100, -100, 100, d, 400);
		c2.loadRotationMatrix( Vec3f(crx*PI/180,cry*PI/180, crz*PI/180) );
		c2.loadTranslation( Vec3f(tx -300, ty - 300, tz - 300) );


		c2.transform(cube, transformedPoints);




		painter.draw( transformedPoints, frame);

		createTrackbar("XRotationBar","Pinhole Camera", &rx, 360);
		createTrackbar("YRotationBar","Pinhole Camera", &ry, 360);
		createTrackbar("ZRotationBar","Pinhole Camera", &rz, 360);

		createTrackbar("NearPlaneDistance","Control Window", &d, 300);

		createTrackbar("XCamRotationBar","Control Window", &crx, 360);
		createTrackbar("YCamRotationBar","Control Window", &cry, 360);
		createTrackbar("ZCamRotationBar","Control Window", &crz, 360);

		createTrackbar("XCamTranslationBar","Control Window", &tx, 600);
		createTrackbar("YCamTranslationBar","Control Window", &ty, 600);
		createTrackbar("ZCamTranslationBar","Control Window", &tz, 600);

		imshow("Pinhole Camera", frame);
		

		//cout << model[0] << endl;
	}

	

	return 0;
}