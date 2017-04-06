#include<opencv2/opencv.hpp>
#include<array>
#include<vector>
#include<iostream>
#include<time.h>

#include "EdgeTest.h"
#include "Utils.h"

#include "ntcore.h"
#include <networktables/NetworkTable.h>


using namespace cv;

int main(int argc, char* argv[])
{
  PiCamera cam(0);

  std::vector<int> lower = {120, 133, 0};
  std::vector<int> upper = {255, 255, 255};

  Mat frame;
  Mat frame_mask;
  Mat filtered_frame;
  Mat frame_edges;

  double offset;
  int sequence = 0;

  NetworkTable *table;

  table -> Shutdown();
  table -> SetClientMode();
  table -> SetTeam(2502);
  table -> Initialize();
  table -> GetTable("PiVision");

  time_t elapsedTime;
  time_t totalElapsedTime;
  
  time_t oldtime = std::time(NULL);
  time_t currenttime = oldtime;
  time_t beginningtime = oldtime;
  while(true)
  {
    frame = cam.getCurrentFrameMultiplier(0.125, 0.125);
    frame_mask = frame;
    inRange(frame, lower, upper, frame_mask);
    bitwise_and(frame, frame, filtered_frame, frame_mask);
    cvtColor(filtered_frame, frame_edges, COLOR_RGB2GRAY);

    offset = middle(frame_edges);

    if(argc > 0)
    {
      imshow("vision", frame_edges);
      std::cout << "offset: " << offset << "\n";
    }

    currenttime = std::time(NULL);
    elapsedTime = currenttime - oldtime;
    totalElapsedTime = currenttime - beginningtime;
    oldtime = currenttime;
    sequence += 1;

    table -> PutNumber("robot_offset", offset);
    table -> PutNumber("fps", 1/elapsedTime);
    table -> PutNumber("avg_fps", sequence/totalElapsedTime);


  }
}
