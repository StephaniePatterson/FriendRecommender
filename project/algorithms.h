#pragma once
#include "datareader.h"
#include <unordered_set>
#include <queue>
#include <stack>
#include <map>
#include <iostream>

using namespace std;

class Algorithms {
    public:
        class ScoredUser
        {
            public:
                unsigned int user;
                int score;
                ScoredUser(unsigned int u, int s)
                {
                    user = u;
                    score = s;
                }
                inline bool operator>(const ScoredUser& other) const 
                {
                    return score > other.score;
                }
        };
        
        // initializes everything necessary for the algorithms functions using a Data Reader
        Algorithms(DataReader d);

        // takes two user IDs and returns whether they are connected
        int bfs(unsigned int user1, unsigned int user2);

        // takes in one user and returns a path that circles back to same user
        vector<unsigned int> eulerianPath(unsigned int user);

        // returns list of connected components for one user
        vector<unsigned int> scc(unsigned int user);

        vector<unsigned int> recommendations(unsigned int user, bool verbose);

    private:
        unordered_map<unsigned int, vector<unsigned int>> graph;

        // helper function for SCC
        void sccHelper(unsigned int user, unsigned int v, map<unsigned int, int>& disc, map<unsigned int, int>& low, stack<unsigned int>& s, map<unsigned int, bool>& inStack, vector<unsigned int>& components);
};