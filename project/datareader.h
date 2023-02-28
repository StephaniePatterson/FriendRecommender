#pragma once
#include <unordered_map>
#include <vector>

using namespace std;

class DataReader 
{
    public:
        //should take the file as a parameter and then initialize unordered map
        DataReader(const string& filename);
        DataReader(const string& filename, bool symmetric_);
        unordered_map<unsigned int, vector<unsigned int>> getGraph();
        void printData();
        unsigned int getMax();
        unsigned int getMin();

    private:
        unordered_map<unsigned int, vector<unsigned int>> graph;
        unsigned int max;
        unsigned int min;
        bool symmetric;
};