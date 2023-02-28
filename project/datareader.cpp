#include "datareader.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

DataReader::DataReader(const string& filename)
{
    symmetric = true;
	ifstream file(filename);
    string line;
    if (file.is_open()) 
    {
        while (getline(file, line)) 
        {
            size_t space = line.find(' ');
            unsigned int first = stoi(line.substr(0, space));
            unsigned int second = stoi(line.substr(space+1));

            if(first < min)
                min = first;
            if(second < min)
                min = second;
            if(first > max)
                max = first;
            if(second > max)
                max = second;

            if(graph.find(first) != graph.end())
            {
            	graph[first].push_back(second);
            }
            else
            {
            	vector<unsigned int> vect{second};
            	graph[first] = vect;
            }
            if(graph.find(second) != graph.end())
            {
                graph[second].push_back(first);
            }
            else
            {
                vector<unsigned int> vect{first};
                graph[second] = vect;
            }
        }
    }
    else
    {
        cout << "File is invalid." << endl;
    }
}

DataReader::DataReader(const string& filename, bool symmetric_) 
{
    symmetric = symmetric_;
    ifstream file(filename);
    string line;
    if (file.is_open()) 
    {
        while (getline(file, line)) 
        {
            size_t space = line.find(' ');
            unsigned int first = stoi(line.substr(0, space));
            unsigned int second = stoi(line.substr(space+1));

            if(first < min)
                min = first;
            if(second < min)
                min = second;
            if(first > max)
                max = first;
            if(second > max)
                max = second;

            if(graph.find(first) != graph.end())
            {
            	graph[first].push_back(second);
            }
            else
            {
            	vector<unsigned int> vect{second};
            	graph[first] = vect;
            }
            if (symmetric) {
                if(graph.find(second) != graph.end())
                {
                    graph[second].push_back(first);
                }
                else
                {
                    vector<unsigned int> vect{first};
                    graph[second] = vect;
                }
            }
        }
    }
    else
    {
        cout << "File is invalid." << endl;
    }
}

unsigned int DataReader::getMax()
{
    return max;
}

unsigned int DataReader::getMin()
{
    return min;
}

unordered_map<unsigned int, vector<unsigned int>> DataReader::getGraph()
{
    return graph;
}

void DataReader::printData()
{
	for( const auto& n : graph ) 
    {
        cout << "Key: " << n.first << "  ";
        cout << "Values " << ":[";
        for (unsigned i = 0; i < n.second.size(); i++)
            cout << n.second[i] << (i < n.second.size() - 1 ? "  " : "]\n");
    }
}