#include<opencv2/opencv.hpp>

#ifndef _utils
#define _utils

using namespace cv;

class PiCamera
{
public:

  VideoCapture capture;
  Mat frame;
  
  PiCamera(int);
  Mat getCurrentFrame();
  Mat getCurrentFrameResized(int, int);
  Mat getCurrentFrameMultiplier(double, double);
  void cleanUp();


};

#endif
