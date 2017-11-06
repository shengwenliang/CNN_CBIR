#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "boost/algorithm/string.hpp"
#include "google/protobuf/text_format.h"
#include "caffe/blob.hpp"
#include "caffe/common.hpp"
#include "caffe/net.hpp"
//#include "caffe/proto/caffe.pb.h"
#include "caffe/util/io.hpp"
#include "caffe/vision_layers.hpp"
#include "extracthash.h"
using namespace caffe;
using std::cout;
using std::endl;
using std::string;
/* 加载模型函数 */
template <typename Dtype>
caffe::Net<Dtype>* loadNet(std::string param_file, std::string pretrained_param_file, caffe::Phase phase)
{
    caffe::Net<Dtype>* net(new caffe::Net<Dtype>(param_file, phase));
    net->CopyTrainedLayersFrom(pretrained_param_file);
    return net;
}
//string query_image,string deploy_path,string model_path,int GPU_Num
NetTy* Extract_Hash(string query_image,string deploy_path,string model_path,int GPU_Num)
{
    cv::Mat src;
    int i=0;
    src = cv::imread(query_image); // 读取测试图片
    cv::resize(src, src, cv::Size(256, 256)); // 这里要将图片resize到prototxt里面的输入层指定的大小
    LOG(INFO) << "------------------" ;
    Caffe::set_mode(Caffe::GPU);
    Caffe::SetDevice(GPU_Num);
    caffe::Net<NetTy>* _net = loadNet<NetTy>(deploy_path, model_path, caffe::TEST); // 加载网络定义文件和参数模型
    caffe::MemoryDataLayer<NetTy> *m_layer = (caffe::MemoryDataLayer<NetTy> *)_net->layers()[0].get(); // 定义个内存数据层指
    std::vector<cv::Mat> dv ; // AddMatVector(const vector<cv::Mat>& mat_vector,const vector<int>& labels)
    dv.push_back(src);
    std::vector<int> label;    // -------------------------------------------------------------------------
    label.push_back(i);
    m_layer->AddMatVector(dv, label);
    std::vector<caffe::Blob<NetTy>*> input_vec;  // 无意义，为了函数参数需要
    _net->Forward(input_vec);                    // 执行一次前向计算
    boost::shared_ptr<caffe::Blob<NetTy> > layerData = _net->blob_by_name("latent_sigmoid");
    const NetTy *pstart = layerData->cpu_data(); // ->cpu_data()返回的是多维数据（数组）
    LOG(INFO) << "------------------4";
    NetTy* res;
    res = new float[48];
    /*-----输出特征-----*/
    for (int i = 0; i < 48; i++)
    {
        //std::cout << *pstart << endl;
    if(*pstart > 0.5)
       std::cout << "1 " << *pstart<<endl;
        else
           std::cout << "0 " << *pstart<<endl;
        res[i] = *pstart;
        //res++;
        pstart++;
    }
    return &res[0];
}
