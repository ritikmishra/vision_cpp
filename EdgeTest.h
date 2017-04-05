#include<vector>
#include<opencv2/opencv.hpp>

#ifndef _edge_test
#define _edge_test

template<typename Object>
int len(std::vector<Object> list);

double avgCalc(std::vector<int> widths);

double middle(cv::Mat img);

#endif
