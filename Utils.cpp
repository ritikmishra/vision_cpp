#include "Utils.h"


using namespace cv;

VideoCapture capture;
Mat frame;

const std::array<std::string, 5> TEST_IMGS = {"HC0_N.png","VC0_C.png","VL0_G.png", "tape.jpg"};

template<typename Object>
int len(std::vector<Object> list)
{
  return list.size();
}

// Calculate the average of a list of numbers
// Confirmed working
double avgCalc(std::vector<double> widths)
{
  try
  {
    double avg = 0;
    const int length = len(widths);
    for(int i = 0; i < length; i++)
    {
      avg = avg + widths[i];
    }
    return avg/length;
  }

  catch(...) { return 0; }

}

// Confirmed working
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

void init(int num)
{
  capture = VideoCapture(0);

  for(int i = 0; i < 10; i++)
  {
    capture >> frame;
  }
}

Mat getCurrentFrame()
{
  capture >> frame;
  // frame = imread(TEST_IMGS[0]);
  return frame;
}

Mat getCurrentFrameResized(int y, int x)
{
  capture >> frame;
  Mat output;
  resize(frame, output, Size(y, x));
  return output;
}

Mat getCurrentFrameMultiplier(int x, int y)
{
  capture >> frame;
  Mat output;
  resize(frame, output, Size(frame.cols * y, frame.rows * x));
  return output;
}

void cleanUp()
{
  capture.release();
  destroyAllWindows();
}


int diff_ms(timeval t1, timeval t2)
{
    return (((t1.tv_sec - t2.tv_sec) * 1000000) +
            (t1.tv_usec - t2.tv_usec))/1000;
}

unsigned long getmsofday() {
   struct timeval tv;
   gettimeofday(&tv, NULL);
   return (long long)tv.tv_sec*1000 + tv.tv_usec/1000;
}

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
