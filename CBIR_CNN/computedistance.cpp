/*************************************************************************
    > File Name: Test.cpp
    > Author:
    > Mail:
    > Created Time: 2017年10月22日 星期日 11时14分33秒
 ************************************************************************/

#include "compute_distance.h"
using namespace cv;
using namespace std;
void deleteAllMark(string &s, const string &mark)
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
bool cmp(const pair<int,unsigned int> &x,const pair<int,unsigned int> &y)
{
    return x.second < y.second;
}

void sortVector(vector<unsigned int> &value, vector<int> &lable)
{
    lable.clear();
    vector<pair<int,unsigned int>> theMap;
    for(vector<unsigned int>::size_type i=0; i<value.size(); i++)
    {
        theMap.push_back(make_pair(i,value[i]));
    }
    sort(theMap.begin(),theMap.end(),cmp);
    for(vector<pair<int,unsigned int>>::size_type i=0; i<theMap.size(); i++)
    {
        lable.push_back(theMap[i].first);
    }
}

void sortVector_float(vector<float> &value, vector<int> &lable)
{
    lable.clear();
    vector<pair<int,float>> theMap;
    for(vector<float>::size_type i=0; i<value.size(); i++)
    {
        theMap.push_back(make_pair(i,value[i]));
    }
    sort(theMap.begin(),theMap.end(),cmp);
    for(vector<pair<int,float>>::size_type i=0; i<theMap.size(); i++)
    {
        lable.push_back(theMap[i].first);
    }
}

unsigned int hamming_distance(const std::string& str1 , const std::string& str2)
{
    if (str1.size() != str2.size()){
      throw std::invalid_argument(
          "Strings passed to hd() must have the same lenght"
      );
    }
    return std::inner_product(
        str1.begin(), str1.end(), str2.begin(),
        0, std::plus<unsigned int>(),
        std::not2(std::equal_to<std::string::value_type>())
    );
}
float euclidean(const vector<float>& v1, const vector<float>& v2)
{
    assert(v1.size() == v2.size());
    float result = 0;
    for(vector<float>::size_type i=0;i!=v1.size();++i)
    {
        result += pow(abs(v1[i] - v2[i]),2);
    }
    return result;
}
template <class Type>
Type stringToNum(const string& str)
{
    istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}
void SplitString(const string& s, vector<float>& v, const string& c)
{
    string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(string::npos != pos2)
    {
        v.push_back(stringToNum<float>(s.substr(pos1, pos2-pos1)));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(stringToNum<float>(s.substr(pos1)));
}

void SplitStrings(const string& s, vector<string>& v, const string& c)
{
    string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}

vector<string> Computing_Distance(string query,vector<float> hash_float_query,vector<float> encode_query,int hamm_or_ecul){
    string s;

    vector<std::string> hashcode;
    vector<std::string> database_file_path;
    vector<std::string> database_label;

    vector<vector<float>> database_encoder;
    vector<vector<float>> database_float_hash;

    ifstream infile_database,infile_database_list_file,infile_database_label,infile_encode_database;

    /*infile_database.open("/home/liangshengwen/kgraph/TestDistance/train_hash_code.txt");
    infile_encode_database.open("/home/liangshengwen/kgraph/TestDistance/train_encode_code.txt");

    infile_database_list_file.open("/home/liangshengwen/DeepBinaryCode/Caffe-DeepBinaryCode-master/data/cifar10/train-file-list.txt");
    infile_database_label.open("/home/liangshengwen/DeepBinaryCode/Caffe-DeepBinaryCode-master/data/cifar10/train-label.txt");*/

    infile_database.open("/home/liangshengwen/ImageNet/ImageNet_train_hash_code.txt");
    infile_encode_database.open("/home/liangshengwen/ImageNet/ImageNet_train_encode_code.txt");

    infile_database_list_file.open("/home/liangshengwen/ImageNet/train.txt");
    infile_database_label.open("/home/liangshengwen/DeepBinaryCode/Caffe-DeepBinaryCode-master/data/cifar10/train-label.txt");

    /*while(getline(infile_database,s))
    {
        deleteAllMark(s," ");
        hashcode.push_back(s);
    }*/
    while(getline(infile_database,s))
    {
        vector<float> v;
        SplitString(s,v," ");
        database_float_hash.push_back(v);
    }

    while(getline(infile_encode_database,s))
    {
        vector<float> v;
        SplitString(s,v," ");
        database_encoder.push_back(v);
    }

    while(getline(infile_database_list_file,s))
    {
        s = s.substr(0,s.find(" "));
        database_file_path.push_back(s);
    }

    while(getline(infile_database_label,s))
    {
        database_label.push_back(s);
    }

    vector<unsigned int>  hamming_dis;
    vector<float> euclidean_result;

    vector<int> encode_label;
    vector<int> label;

    vector<string> back_result;
    int a=0;
    if(hamm_or_ecul == 0) //hamming
    {
        //cout<<database_file_path.size()<<endl;
        boost::timer::auto_cpu_timer timer;
        clock_t start1 = clock();
        double cost_time = 0;
        /*for(auto iter=hashcode.begin();iter!=hashcode.end();++iter)
        {
            //cout<<*iter<<endl;
            clock_t start = clock();
            float result = hamming_distance(*iter,query);
            clock_t end = clock();
            cost_time += (double)(end-start);
            hamming_dis.push_back(result);
            //cout<<hamming_distance(*iter,query)<<endl;
        }*/

        for(auto iter=database_float_hash.begin();iter!=database_float_hash.end();++iter)
        {
            //cout<<*iter<<endl;
            clock_t start = clock();
            float result = euclidean(hash_float_query,*iter);
            clock_t end = clock();
            cost_time += (double)(end-start);
            hamming_dis.push_back(result);
            //cout<<hamming_distance(*iter,query)<<endl;
        }

        float time=0;
        time = timer.elapsed().wall / 1e9;
        //cout<<"time-elapsed--"<<time<<endl;
        clock_t end1 = clock();
        //cout<<"out for time---"<<(double)(end1-start1)/CLOCKS_PER_SEC<<endl;
        //cout<<"in for time---"<<cost_time/CLOCKS_PER_SEC<<endl;

        sortVector(hamming_dis,label);
        clock_t sort_hamming_end = clock();
        cout<<"sort hamming  cost time---"<<(double)(sort_hamming_end-start1)/CLOCKS_PER_SEC<<endl;
        cout<<label.size()<<endl;
        for(auto iter=label.begin();iter!=label.end();++iter)
        {
            //cout<<*iter<<endl;
            if(a<200)
            {
                //cout<<*iter<<"ham++++"<<database_file_path.at(*iter)<<endl;
                back_result.push_back("/home/liangshengwen/ImageNet/ILSVRC2012_img_train/"+database_file_path.at(*iter));
            }
            //back_result.push_back("/home/liangshengwen/ImageNet/ILSVRC2012_img_train/"+database_file_path.at(*iter));
            a++;
        }
    }
    else   //euclidean
    {
        clock_t encode_start= clock();
        for(auto iter=database_encoder.begin();iter!=database_encoder.end();++iter)
        {
            euclidean_result.push_back(euclidean(encode_query,*iter));
    //        cout<<euclidean(encode_query_test,*iter)<<endl;
        }

        //cout<<"encode cost time---"<<(double)(encode_end-encode_start)/CLOCKS_PER_SEC<<endl;

        sortVector_float(euclidean_result,encode_label);
        clock_t sort_encode_end = clock();
        cout<<"sort_encode cost time---"<<(double)(sort_encode_end-encode_start)/CLOCKS_PER_SEC<<endl;
        for(auto iter=encode_label.begin();iter!=encode_label.end();++iter)
        {
            //cout<<*iter<<endl;
            if(a<200)
            {
                //cout<<*iter<<"ecu---"<<database_file_path.at(*iter)<<database_label.at(*iter)<<endl;
                back_result.push_back("/home/liangshengwen/ImageNet/ILSVRC2012_img_train/"+database_file_path.at(*iter));

            }
            a++;
        }
    }
    return back_result;
}
