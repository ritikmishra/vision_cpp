#include<opencv2/opencv.hpp>

#ifndef _utils
#define _utils

using namespace cv;

class Picamera
{
public:

  Mat getCurrentFrame();
  Mat getCuurrentFrameResized(int x, int y);
  Mat getCuurrentFrameMultiplier(double x, double y);
  void cleanUp();


};

#endif
