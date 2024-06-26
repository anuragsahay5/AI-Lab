#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

#define INF = 1e9;

// Function to calculate total distance of the travel path
int calculateDistance(const vector<vector<int>> &graph, const vector<int> &path)
{
    int dist = 0;
    int n = path.size();
    for (int i = 0; i < n - 1; ++i)
    {
        dist += graph[path[i]][path[i + 1]];
    }
    dist += graph[path.back()][path[0]];
    return dist;
}

vector<int> hillClimbTSP(const vector<vector<int>> &graph, int &start)
{
    int n = graph.size();
    vector<int> path(n);
    for (int i = 0; i < n; ++i)
    {
        path[i] = i;
    }
    swap(path[0],path[start]); // to start from start_city

    // Calculate initial distance
    int minDistance = calculateDistance(graph, path);

    random_shuffle(path.begin()+1,path.end()); //randomly set the initial path route

    // Hill climbing
    bool improved = true;
    while (improved)
    {
        improved = false;
        for (int i = 1; i < n - 1; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                swap(path[i], path[j]); // Swap two cities in the path
                int newDistance = calculateDistance(graph, path);
                if (newDistance < minDistance) // check if distance is improved
                {
                    minDistance = newDistance;
                    improved = true;
                }
                else
                {
                    swap(path[i], path[j]); // Revert the swap if it doesn't improve the distance
                }
            }
        }
    }
    return path;
}

int main()
{
    // Adjacency matrix
    vector<vector<int>> graph = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}};

    int startCity = 1; // Starting city

    vector<int> path = hillClimbTSP(graph, startCity);

    // Output the path
    cout << "Optimal Path: ";
    for (int city : path)
    {
        cout << city << " ";
    }
    cout << "\n";

    // Output the total distance
    cout << "Total Distance: " << calculateDistance(graph, path) << endl;

    return 0;
}
