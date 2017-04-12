#include "Utils.h"


using namespace cv;

VideoCapture capture;
Mat frame;

const std::array<std::string, 5> TEST_IMGS = {"HC0_N.png","VC0_C.png","VL0_G.png", "tape.jpg"};

// Calculate the average of a list of numbers
double avgCalc(std::vector<double> widths)
{
  try
  {
    double avg = 0;
    const int length = widths.size();
    for(int i = 0; i < length; i++)
    {
      avg = avg + widths[i];
    }
    return avg/length;
  }

  catch(...) { return 0; }

}

// Calculate how offcenter the vision tape is
double middle(Mat img)
{
  double avg = 0;
  std::vector<double> graph;
  Mat column;
  for(int x = 0; x < img.size().width; x++)
  {
    column = img.col(x);
    graph.push_back(sum(column)[0]/sum(img)[0]);
  }

  for(unsigned int x = 0; x < graph.size(); x++)
  {
    avg += x * graph[x];
  }
  avg = avg - img.size().width/2;

  return avg;
}

// start reading from the camera
void init(int num)
{
  capture = VideoCapture(0);

  for(int i = 0; i < 10; i++)
  {
    capture >> frame;
  }
}

// return the current frame from the camera
Mat getCurrentFrame()
{
  capture >> frame;
  // frame = imread(TEST_IMGS[0]);
  return frame;
}

// return the current frame from the camera, resized with dimensions
Mat getCurrentFrameResized(int y, int x)
{
  capture >> frame;
  Mat output;
  resize(frame, output, Size(y, x));
  return output;
}

// return the current frame from the camera, resized with a multiplier
Mat getCurrentFrameMultiplier(int x, int y)
{
  capture >> frame;
  Mat output;
  resize(frame, output, Size(frame.cols * y, frame.rows * x));
  return output;
}

// clean up
void cleanUp()
{
  capture.release();
  destroyAllWindows();
}

// get the difference between 2 millisecond counts of type timeval. Used for fps calculations
int diff_ms(timeval t1, timeval t2)
{
    return (((t1.tv_sec - t2.tv_sec) * 1000000) +
            (t1.tv_usec - t2.tv_usec))/1000;
}

// get the time of day in milliseconds. Used for fps calculations
unsigned long getmsofday() {
   struct timeval tv;
   gettimeofday(&tv, NULL);
   return (long long)tv.tv_sec*1000 + tv.tv_usec/1000;
}

// A main() function for testing
// int main(int argc, char** args)
// {
//   timeval startTime, endTime;
//   int sequence = 0;
//   init(0);
//   // Mat img = imread(TEST_IMGS[0], 0);
//
//
//   while(true) {
//
//     ++sequence;
//     imshow("2", getCurrentFrame());
//     waitKey(1);
//
//     gettimeofday(&endTime, 0);
//
//     std::cout << sequence/diff_ms(endTime, startTime) << "\n";
//
//
//   }
//   return 0;
// }
