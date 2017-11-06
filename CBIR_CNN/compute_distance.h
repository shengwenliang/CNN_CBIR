#ifndef COMPUTE_DISTANCE_H
#define COMPUTE_DISTANCE_H
#include<iostream>
#include<fstream>
#include<cassert>
#include<string>
#include<algorithm>
#include<vector>
#include<time.h>
#include<functional>
#include<boost/timer/timer.hpp>
#include<boost/program_options.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/opencv.hpp>
using namespace std;
vector<string> Computing_Distance(string query,vector<float> hash_float_query,vector<float> encode_query,int hamm_or_ecul);
#endif // COMPUTE_DISTANCE_H
