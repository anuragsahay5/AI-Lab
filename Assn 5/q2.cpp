#include <bits/stdc++.h>

using namespace std;

// Define cell movement directions
const int dx[] = {-1, 1, 0, 0}; // Up, Down, Left, Right
const int dy[] = {0, 0, -1, 1};
const char directions[] = {'U', 'D', 'L', 'R'};

// Node structure to represent state
struct Node
{
    int x, y, cost;
    string path;
    vector<vector<bool>> visited; // Record visited states to prevent revisiting cells
    bool operator<(const Node &other) const
    {
        return cost > other.cost; // For min priority queue
    }
};

// Function to check if the cell is within the grid and not an obstacle
bool isValid(int x, int y, int n, const vector<vector<int>> &grid, const vector<vector<bool>> &visited)
{
    return x >= 0 && x < n && y >= 0 && y < n && grid[x][y] != 0 && !visited[x][y];
}

// AO* search function
vector<string> AOStar(const vector<vector<int>> &grid)
{
    int n = grid.size();
    vector<vector<int>> heuristic(n, vector<int>(n, 0)); // Since we're exploring all paths, heuristic is not used
    priority_queue<Node> pq;
    vector<string> paths;

    pq.push({0, 0, 0, "", vector<vector<bool>>(n, vector<bool>(n, false))});

    while (!pq.empty())
    {
        Node cur = pq.top();
        pq.pop();

        // Check if current cell is the destination
        if (cur.x == n - 1 && cur.y == n - 1)
        {
            paths.push_back(cur.path);
            continue;
        }

        // Mark the current cell as visited
        cur.visited[cur.x][cur.y] = true;

        for (int i = 0; i < 4; ++i)
        {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];

            if (isValid(nx, ny, n, grid, cur.visited))
            {
                int new_cost = cur.cost + 1; // Cost of moving to adjacent cell

                // Push new state to priority queue
                pq.push({nx, ny, new_cost, cur.path + directions[i], cur.visited});
            }
        }
    }
    return paths;
}

int main()
{
    vector<vector<int>> grid{
        {1, 1, 1},
        {1, 1, 0},
        {1, 1, 1}};

    vector<string> paths = AOStar(grid);
    cout << "Possible paths\n";
    for (const string &path : paths)
    {
        cout << path << endl;
    }

    return 0;
}
