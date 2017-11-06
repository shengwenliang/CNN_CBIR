/*************************************************************************
    > File Name: TestKnn.cpp
    > Author:
    > Mail:
    > Created Time: 2017年10月24日 星期二 10时46分10秒
 ************************************************************************/

#include<iostream>
#include<vector>
#include <boost/timer/timer.hpp>
#include <boost/program_options.hpp>
#include <time.h>
#include <QFile>
#include <kgraph.h>
#include <kgraph-data.h>
#include "qt_kgraph.h"
using namespace std;
using namespace kgraph;


vector<std::string> database_file_path;
Matrix<float> data(1281167,48);

void deletesAllMark(string &s, const string &mark)
{
    unsigned int nSize = mark.size();
    while(1)
    {
        string::size_type pos = s.find(mark);
        if(pos == string::npos)
        {
            return;
        }
        s.erase(pos, nSize);
    }
}
template <class Type>
Type stringToNum(const string& str)
{
    istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}
void initial()
{
    string s;
    ifstream infile_database,infile_database_list_file;
    vector<std::string> hashcode;

    infile_database.open("/home/liangshengwen/ImageNet/ImageNet_train_hash_code.txt");
    infile_database_list_file.open("/home/liangshengwen/ImageNet/train.txt");

    while(getline(infile_database,s))
    {
        deletesAllMark(s," ");
        hashcode.push_back(s);
    }
    while(getline(infile_database_list_file,s))
    {
        s = s.substr(0,s.find(" "));
        database_file_path.push_back(s);
    }

    int i=0;
    for(auto iter=hashcode.begin();iter!=hashcode.end();++iter)
    {
        for(int j=0;j<48;j++)
        {
            data[i][j] = stringToNum<float>((*iter).substr(j,1));
        }
        i++;
    }
}

vector<string> mains(float *query)
{
    //Matrix<float> data(hashcode.size(),48);
    unsigned dim = data.dim();
    VectorOracle<Matrix<float>, float const*> oracle(data,
            [dim](float const *a, float const *b)
            {
                float r = 0;
                for (unsigned i = 0; i < dim; ++i) {
                    float v = float(a[i]) - (b[i]);
                    r += v * v;

                    //int v = int((int)a[i]^(int)b[i]);
                    //cout<<a[i]<<"--"<<b[i]<<"--"<<v<<endl;
                    //r +=v;
                }
                return r;
            });
    KGraph *kgraph = KGraph::create();
    KGraph::SearchParams Sparams;
    Sparams.K = 200;
    //params.P = P;
    QFile file("/home/liangshengwen/ImageNet/ImageNet_index.txt");
    if(file.exists())
    {
        kgraph->load("/home/liangshengwen/ImageNet/ImageNet_index.txt");
    }
    else
    {
        cout<<"need update"<<endl;
    }

    /*{
        KGraph::IndexParams params;
        //params.reverse = -1;
        kgraph->build(oracle, params, NULL);
        kgraph->save("/home/liangshengwen/ImageNet/ImageNet_index.txt");
    }*/
    boost::timer::auto_cpu_timer timer;
    vector<unsigned> result(200);
    KGraph::SearchInfo info;
    //result.resize(10, 1000);
    clock_t start = clock();
    kgraph->search(oracle.query(query),Sparams,&result[0],&info);
    clock_t end = clock();
    cout<<"time cost---"<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
    cout<<"info.cost---"<<info.cost<<endl;
    vector<string> back_result;
    /*for(int i=0;i<5;i++)
    {
        //cout<<result[0][i]<<endl;
        cout<<"ham++++"<<database_file_path.at(result.at(i))<<endl;
        back_result.push_back("/home/liangshengwen/ImageNet/ILSVRC2012_img_train/"+database_file_path.at(result.at(i)));
    }*/
    for(auto iter=result.begin();iter!=result.end();++iter)
    {
        //cout<<*iter<<endl;
        //cout<<"ham++++"<<database_file_path.at(*iter)<<endl;
        back_result.push_back("/home/liangshengwen/ImageNet/ILSVRC2012_img_train/"+database_file_path.at(*iter));
    }
    float time=0;
    time = timer.elapsed().wall / 1e9;
    cout<<"time-elapsed--"<<time<<endl;
    return back_result;
    //cout<<data.size()<<endl;
    //cout<<data.dim()<<endl;
}


