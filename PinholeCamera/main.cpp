#include <cstdlib>
#include <cstdio>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "PinholeCamera.h"
#include <opencv2/calib3d/calib3d.hpp>
#include "Polygon.h"



using namespace cv;
using namespace std;

int d = 50;

float K[] = { 1, 0, 340.0f/d, 0,
					  0, 1, 240.0f/d, 0,
	                  0, 0, 1, 0,
					  0, 0, 1.0f/d, 0};

float RT[] = {1, 0, 0, 0,
	0, -1, 0, 0,
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

	Mat frame(Size(640,480), CV_8UC3);

	Mat k(4,4,CV_32FC1,K);
	Mat rt(4,4, CV_32FC1, RT);

	
	//c.center.x = 340.0f;
	//c.center.y = 240.0f;
	pinholeCamera::PinholeCamera c(d, Point(0, 0), Mat(Point3f(0,0,0)), Mat(Point3f(0,0,-100)));


	while(waitKey(10) < 0){

		

		c.rotateCamera(crx*PI/180,cry*PI/180, crz*PI/180);
		c.translateCamera( tx -300, ty - 300, tz - 300);
		c.setProjectionDepth(d);
		

		frame.release();

		frame = Mat(Size(640,480), CV_8UC3);		

		c.transform(cube);


		Scalar s[] = {Scalar(0,0,255), Scalar(0,255,0), Scalar(255,0,0) };

		//cout << (cube.pixels[0]) << endl;
		for(int i = 0; i < cube.pixels.size(); i++)
		{

			Point p = cube.pixels[i] + Point(320,240);

			if( i == 0 ) cout << p << endl;

			if( p.x < 0 || p.x > 640 || p.y < 0 || p.y > 480 ) continue;
			
			circle(frame, p, 1, s[i%4], 1);
			//circle(frame, projection[i], 1, Scalar(0,0,0), 1);
		}



		

		

		cube.rx = rx*PI/180;
		cube.ry = ry*PI/180;
		cube.rz = rz*PI/180;

		

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