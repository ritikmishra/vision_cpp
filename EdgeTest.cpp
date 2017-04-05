#include<opencv2/opencv.hpp>
#include<array>
#include<vector>
#include<iostream>

using namespace cv;
using namespace std;

const array<string, 5> TEST_IMGS = {"HC0_N.png","VC0_C.png","VL0_G.png", "tape.jpg"};

template<typename Object>
int len(vector<Object> list)
{
  return list.size();
}

// Calculate the average of a list of numbers
double avgCalc(vector<int> widths)
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

double middle(Mat img)
{
  double avg = 0;
  vector<double> graph;
  Mat column;
  for(int x = 0; x < img.size().width; x++)
  {
    column = img.col(x);
    graph.push_back(sum(column)[0]/sum(img)[0]);
  }

  for(int x = 0; x < graph.size(); x++)
  {
    avg += x * graph[x];
  }
  avg = avg - img.size().width/2;

  return avg;
}

int main(int, char**)
{

  for(int i = 0; i < TEST_IMGS.size(); i++)
  {
    cout << middle(imread(TEST_IMGS[i], 0)) << "\n";
  }
  return 0;
}
