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

  unsigned long startTime;
  unsigned long beginTime = getmsofday();
  unsigned long endTime;

  double sequence = 0;

  double offset;

  double currentFPS;
  double averageFPS;

  // initalize cameras
  init(0);

  // define lower and upper bounds for colors
  Scalar lower = {120, 133, 0};
  Scalar upper = {255, 255, 255};

  // make a magical pointer for NetworkTables
  NetworkTable *table;

  // We shutdown NetworkTables before starting it back up just in case.
  table -> Shutdown();
  table -> SetClientMode();
  table -> SetTeam(2502);
  table -> Initialize();
  table -> GetTable("PiVision");

  // Create appropriate matrixes
  Mat frame = getCurrentFrame();
  Mat frame_mask(frame.size(), frame.type());

  // run vision forever
  while(true)
  {
    // start timer
    startTime = getmsofday();

    // look through camera
    frame = getCurrentFrame();

    // generate frame_mask such that if the color of the pixel at (x, y) in frame is between the colors Scalar lower and Scalar upper, then (x, y) in frame_mask is white. Otherwise, (x, y) is black
    inRange(frame, lower, upper, frame_mask);

    // calculate offset from the center of the screen
    offset = middle(frame_mask);

    // end timer
    endTime = getmsofday();

    // add 1 to our counter
    ++sequence;

    // calculate FPS's
    currentFPS = 1000 * (1.0/(endTime - startTime));
    averageFPS = 1000 * (sequence/(endTime - beginTime));

    // log debug info to the console if appropriate debug options set
    if(argc > 1)
    {
      std::cout << "offset: " << offset << "\n";
      std::cout << "fps: " << currentFPS << "\n";
      std::cout << "avgfps: " << averageFPS << "\n" << "\n";
    }

    // show the frame mask if appropriate debug options set
    if(argc > 2)
    {
      imshow("vision", frame_mask);
      waitKey(1);
    }

    // show the regular frame if appropriate debug options set
    if(argc > 3)
    {
      imshow("camera", frame);
      waitKey(1);
    }

    // send data to roborio
    // this might cause segfaults if no connection to a networktable!
    table -> PutNumber("sequence", sequence);
    table -> PutNumber("robot_offset", offset);
    table -> PutNumber("fps", currentFPS);
    table -> PutNumber("avg_fps", averageFPS);

  }
}
