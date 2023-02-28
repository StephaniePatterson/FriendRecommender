#include "algorithms.h"
#include <unordered_set>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

Algorithms::Algorithms(DataReader d)
{
    graph = d.getGraph();
}

int Algorithms::bfs(unsigned int user1, unsigned int user2) 
{
    // variables needed for BFS
    unordered_map<unsigned int, unsigned int> distance;
    queue<int> search;

    // initialize using the start user's value
    search.push(user1);
    distance[user1] = 0;

    // do the search
    while(!search.empty())
    {
        // get the next node to search
        unsigned int top = search.front();
        search.pop(); 

        // if the target node is found, return the distance
        if(top == user2) 
            return distance[top];

        // add each of the neighbors of the current node to the search queue
        for(unsigned int i: graph[top]) 
        {
            // if the node has not been visited before (it won't be in the keys of distance)
            if(distance.find(i) == distance.end())
            {
                search.push(i);
                distance[i] = distance[top] + 1;
            }
        }
    }
    return -1;
}

vector<unsigned int> Algorithms::eulerianPath(unsigned int user) 
{
    for(auto& node: graph)
        if(node.second.size()% 2 != 0)
        {
            cout << "Not all graph nodes have an even degree!" << endl;
            return vector<unsigned int>();
        }
    unordered_map<unsigned int, vector<unsigned int>> graphCopy = graph;

    stack<unsigned int> currentPath;    //store the vertices
    vector<unsigned int> eulerianCircuit; //the path that will be printed

    currentPath.push(user);
    int currentVertex = user;

    while(!currentPath.empty())
    {
       //if there are remaining edges
       if(!graphCopy[currentVertex].empty())
       {
           currentPath.push(currentVertex); 
           int nextVertex = graphCopy[currentVertex].back();

           graphCopy[currentVertex].pop_back(); // remove the edge
           graphCopy[nextVertex].erase(remove(graphCopy[nextVertex].begin(), graphCopy[nextVertex].end(), currentVertex), graphCopy[nextVertex].end()); // remove the reverse edge

           currentVertex = nextVertex;
       }
       else
       {
           eulerianCircuit.push_back(currentVertex);
           currentVertex = currentPath.top();
           currentPath.pop();
       }
    }

    return eulerianCircuit;
}
        
vector<unsigned int> Algorithms::scc(unsigned int user) 
{
    if (graph.find(user) == graph.end()) {
        return vector<unsigned int>();
    }

    //initialize data structures needed for SCC
    map<unsigned int, int> disc; //stores the time each node was visited for the first time
    map<unsigned int, int> low; //stores the highest reachable ancestor from each node
    stack<unsigned int> s; //stack to be used for DFS traversal
    map<unsigned int, bool> inStack; //stores whether something is in the stack
    vector<unsigned int> components; //the strongly connected component that contains the user

    //iterate through graph and call helper function on each vertex
    for (auto elem : graph)
        if (disc.find(elem.first) == disc.end())
            sccHelper(user, elem.first, disc, low, s, inStack, components);
    return components;
}

void Algorithms::sccHelper(unsigned int user, unsigned int v, map<unsigned int, int>& disc, map<unsigned int, int>& low, stack<unsigned int>& s, map<unsigned int, bool>& inStack, vector<unsigned int>& components) 
{
    static int counter = 0; //keeps track of how many times helper has been called so that disc can be updated with when each vertex was first visited
    counter++;
    disc[v] = counter;
    low[v] = counter;

    s.push(v);
    inStack[v] = true;

    //iterate through vertexes adjacent to current vertex
    for (unsigned i = 0; i < graph[v].size(); i++) 
    {
        unsigned int cur = graph[v][i];
        
        //if a vertex hasn't been visited, call helper function on it
        if (disc.find(cur) == disc.end()) 
        {
            sccHelper(user, cur, disc, low, s, inStack, components);

            //if an adjacent vertex's low value is lower than the current vertex's, update current vertex's
            low[v] = min(low[v], low[cur]);

        } 
        else if (inStack[cur] == true) //only update low value if the current adjacent vertex is already in the stack
        {
            low[v] = min(low[v], disc[cur]);
        }
    }

    //if low is equal to disc, we are at the head of a strongly connected component
    if (low[v] == disc[v]) 
    {
        vector<unsigned int> vect; //to store scc
        bool relevant = false; //condition to check if this scc is the one we want
        while (s.top() != v) 
        {
            //if we're at the vertex for the user we're looking for, then this is the scc we want
            if (s.top() == user)
                relevant = true;
            
            vect.push_back(s.top());
            inStack[s.top()] = false;
            s.pop();
        }
        vect.push_back(s.top());
        
        inStack[s.top()] = false;
        s.pop();

        //if we found the correct scc, update components with vect
        if (relevant || v == user)
            components = vect;
    }
}

vector<unsigned int> Algorithms::recommendations(unsigned int user, bool verbose)
{
    vector <unsigned int> stronglyConnected = scc(user);
    vector <unsigned int> path = eulerianPath(user);
    vector <unsigned int> recs;
    priority_queue <ScoredUser, vector<ScoredUser>, greater<ScoredUser>> scores; 

    for(auto elem : stronglyConnected) // for each recommendation in the strongly connected component
    {
        // if the user is not itself or one of its current friends
        if(elem == user || count(graph[user].begin(), graph[user].end(), elem))
            continue;

        // calculate a recommendation score with the distance between the users using bfs and eulerian path
        int distance = bfs(user, elem);
        if(verbose)
            cout << "The distance between " << user << " and " << elem << " is: " << distance << "." << endl;
        int score = 10 * distance - count(path.begin(), path.end(), elem);
        
        scores.push(ScoredUser(elem, score)); // place recommendations into a min heap based on the score
    }
    if(verbose)
    {
        cout << endl;
        cout << "The Eulerian Circuit for " << user << " is: " << endl;
        for(unsigned int i = 0; i < path.size(); i++)
            cout<< path[i] << (i < path.size() - 1 ? "->" : "\n");
        cout << endl;

        cout << "The Strongly Connected Component that includes " << user << " is: " << endl;
        for (unsigned i = 0; i < stronglyConnected.size(); i++) 
            cout << stronglyConnected[i] << " ";
        cout << endl;
    }
            
    for(unsigned int i = 0; i < 10 && !scores.empty(); i++)
    {
        // pop the top 10 (or less if there are not 10 recommendations) and put them in a vector to return
        recs.push_back(scores.top().user);
        scores.pop();
    }

    return recs;
}