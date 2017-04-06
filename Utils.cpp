#include<opencv2/opencv.hpp>
#include "Utils.h"

using namespace cv;

class PiCamera
{
public:
  VideoCapture capture;
  Mat frame;


  PiCamera(int camnum);
  
  Mat getCurrentFrame()
  {
    capture >> frame;
    return frame;
  }

  Mat getCurrentFrameResized(int x, int y)
  {
    Mat retval;
    resize(getCurrentFrame(), retval, Size(x,y));
    return retval;
  }

  Mat getCurrentFrameMultiplier(double x, double y)
  {
    frame = getCurrentFrame();
    Mat retval;
    resize(frame, retval, Size(frame.cols * x, frame.rows * y));
    return retval;
  }

  void cleanUp()
  {
    capture.release();
    destroyAllWindows();
  }


};

PiCamera::PiCamera(int camnum)
{
  VideoCapture capture(camnum);

  for(int i = 0; i < 10; i++)
  {
    capture >> frame;
  }
}
