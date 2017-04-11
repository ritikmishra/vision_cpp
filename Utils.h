#include<opencv2/opencv.hpp>
#include <sys/time.h>

#ifndef _edge_test
#define _edge_test

template<typename Object>
int len(std::vector<Object> list);

double avgCalc(std::vector<int> widths);

double middle(cv::Mat img);

void init(int);

cv::Mat getCurrentFrame();

cv::Mat getCurrentFrameResized(int, int);

cv::Mat getCurrentFrameMultiplier(int, int);

void cleanUp();

int diff_ms(timeval, timeval);

unsigned long getmsofday();

#endif
