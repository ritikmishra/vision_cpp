#include<opencv2/opencv.hpp>
#include<array>
#include<vector>
#include<iostream>
#include<time.h>

#include "Utils.h"

#include "ntcore.h"
#include <networktables/NetworkTable.h>


using namespace cv;

int main(int argc, char* argv[])
{

  init(0);

  Scalar lower = {120, 133, 0};
  Scalar upper = {255, 255, 255};


  NetworkTable *table;

  table -> Shutdown();
  // table -> SetClientMode();
  // table -> SetTeam(2502);
  // table -> Initialize();
  // table -> GetTable("PiVision");

  unsigned long startTime;
  unsigned long beginTime = getmsofday();
  unsigned long endTime;

  double sequence = 0;

  double offset;

  double currentFPS;
  double averageFPS;

  Mat frame = getCurrentFrame();
  Mat frame_mask(frame.size(), frame.type());
  Mat filtered_frame(frame.size(), frame.type());
  Mat frame_edges(frame.size(), frame.type());

  while(true)
  {
    startTime = getmsofday();
    frame = getCurrentFrameResized(1920, 1080);

    inRange(frame, lower, upper, frame_mask);

    filtered_frame = Mat(frame.size(), frame.type());
    bitwise_and(frame, frame, filtered_frame, frame_mask);

    cvtColor(filtered_frame, frame_edges, COLOR_RGB2GRAY);

    offset = middle(frame_edges);
    endTime = getmsofday();

    ++sequence;

    currentFPS = 1000 * (1.0/(endTime - startTime));
    averageFPS = 1000 * (sequence/endTime - beginTime);

    if(argc > 0)
    {
      imshow("vision", frame_edges);
      std::cout << "offset: " << offset << "\n";
      std::cout << "fps: " << currentFPS << "\n";
      std::cout << "avgfps: " << averageFPS << "\n" << "\n";
      waitKey(1);
    }


    // table -> PutNumber("robot_offset", offset);
    // table -> PutNumber("sequence", sequence);

    // table -> PutNumber("fps", currentFPS);
    // table -> PutNumber("avg_fps", averageFPS);


  }
}
