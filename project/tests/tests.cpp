#include "../cs225/catch/catch.hpp"
#include "../algorithms.h"
#include "../datareader.h"
#include <unordered_map>


TEST_CASE("BFS: test empty graph") 
{
    DataReader d("tests/empty.txt");
    Algorithms algos(d);
    REQUIRE(algos.bfs(1, 0) == -1);
}

TEST_CASE("BFS: test user1 not in graph") 
{
    DataReader d("tests/500nodes.txt");
    Algorithms algos(d);
    REQUIRE(algos.bfs(501, 1) == -1);
}

TEST_CASE("BFS: test user2 not in graph") 
{
    DataReader d("tests/500nodes.txt");
    Algorithms algos(d);
    REQUIRE(algos.bfs(1, 501) == -1);
}

TEST_CASE("BFS: test user1 same as user2") 
{
    DataReader d("tests/500nodes.txt");
    Algorithms algos(d);
    REQUIRE(algos.bfs(1, 1) == 0);
}

TEST_CASE("BFS: user1 and user2 are not connected") 
{
    DataReader d("tests/500nodes.txt");
    Algorithms algos(d);
    REQUIRE(algos.bfs(1, 60) == -1);
}

TEST_CASE("BFS: test distance from user1 to user2") 
{
    DataReader d("tests/500nodes.txt");
    Algorithms algos(d);

    REQUIRE(algos.bfs(0, 30) == 2);
    REQUIRE(algos.bfs(1, 12) == 3);
    REQUIRE(algos.bfs(3, 40) == 4);
    REQUIRE(algos.bfs(45, 49) == 3);
    REQUIRE(algos.bfs(60, 61) == 2);
}

TEST_CASE("Tarjan's SCC: test empty graph")
{
    DataReader d("tests/empty.txt");
    Algorithms alg(d);
    REQUIRE(alg.scc(1).empty());
}

TEST_CASE("Tarjan's SCC: test user not in graph")
{
    DataReader d("tests/500nodes.txt");
    Algorithms alg(d);
    REQUIRE(alg.scc(501).empty());
}

TEST_CASE("Tarjan's SCC: test SCC on asymmetric dataset")
{
    DataReader d("tests/small_file.txt", false);
    Algorithms alg(d);
    vector<unsigned int> solution1 = {8, 9};
    REQUIRE(alg.scc(8) == solution1);
    vector<unsigned int> solution2 = {7};
    REQUIRE(alg.scc(7) == solution2);
    vector<unsigned int> solution3 = {5, 4, 6};
    REQUIRE(alg.scc(6) == solution3);
    vector<unsigned int> solution4 = {1, 0, 2, 3};
    REQUIRE(alg.scc(1) == solution4);
}

TEST_CASE("Tarjan's SCC: test SCC on symmetric dataset")
{
    DataReader d("tests/small_file.txt");
    Algorithms alg(d);
    vector<unsigned int> solution = {3, 0, 1, 2, 6, 4, 5, 7, 9, 8};
    REQUIRE(alg.scc(4) == solution);
}

TEST_CASE("Recommendations: test empty graph") 
{
    DataReader d("tests/empty.txt");
    Algorithms algos(d);
    REQUIRE(algos.recommendations(1, false).empty());
}

TEST_CASE("Recommendations: test user not in graph") 
{
    DataReader d("tests/500nodes.txt");
    Algorithms algos(d);
    REQUIRE(algos.recommendations(501, false).empty());
}

TEST_CASE("Recommendations: test recommendations") 
{
    DataReader d("tests/500nodes.txt");
    Algorithms algos(d);
    vector<unsigned int> recs = algos.recommendations(0, false);
    vector<unsigned int> solution = {49, 28, 27, 25, 41, 15, 26, 3, 4, 9};
    REQUIRE(recs.size() == solution.size());
    for(auto r : recs)
        REQUIRE(count(solution.begin(), solution.end(), r));
}
