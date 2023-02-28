#include "datareader.h"
#include "algorithms.h"
#include <iostream>

int main() 
{
    cout << "Hello!! Welcome to our Facebook friend recommendations project!" << endl;
    cout << "To get started, enter a appropriate file name! You can find some in the tests directory." << endl; 
    cout << "The full facebook data set containing over 4000 nodes can be found at tests/facebook_combined.txt." << endl; 
    cout << "A smaller data set containing 500 nodes can be found at tests/500nodes.txt." << endl;
    cout << "Enter filename: ";

    string filename;
    cin >> filename;

    DataReader d(filename);
    Algorithms algos(d);

    if(d.getMin() == 0 && d.getMax() == 0)
        return 0;

    unsigned int i;
    cout << "Enter a user between " << d.getMin() << " and " << d.getMax() << " to get the recommended friends: ";
    cin >> i;

    if(i < d.getMin() || i > d.getMax())
    {
        cout << "Invalid user." << endl;
        return 0;
    }

    bool verbose;
    cout << "Enter 1 for verbose mode on (not recommended for the large dataset) or 0 for verbose mode off: ";
    cin >> verbose;

    cout << endl;
    vector <unsigned int> recs = algos.recommendations(i, verbose);
    cout << endl;
    cout << "Recommendations for " << i << ": "<< endl;
    for(auto r : recs)
        cout << r << endl;
    

    cout << endl;

    return 0;
}