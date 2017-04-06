#include<opencv2/opencv.hpp>
#include "Utils.h"

using namespace cv;

Mat PiCamera::getCurrentFrame()
{
  capture >> frame;
  return frame;
}

Mat PiCamera::getCurrentFrameResized(int x, int y)
{
  Mat retval;
  resize(getCurrentFrame(), retval, Size(x,y));
  return retval;
}

Mat PiCamera::getCurrentFrameMultiplier(double x, double y)
{
  frame = getCurrentFrame();
  Mat retval;
  resize(frame, retval, Size(frame.cols * x, frame.rows * y));
  return retval;
}

void PiCamera::cleanUp()
{
  capture.release();
  destroyAllWindows();
}

PiCamera::PiCamera(int camnum)
{
  VideoCapture capture(camnum);

  for(int i = 0; i < 10; i++)
  {
    capture >> frame;
  }
}
