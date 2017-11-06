#ifndef EXTRACTHASH_H
#define EXTRACTHASH_H
#define NetTy float
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include "mainwindow.h"
using namespace std;
NetTy* Extract_Hash(string query_image,string deploy_path,string model_path,int GPU_Num);
#endif // EXTRACTHASH_H
