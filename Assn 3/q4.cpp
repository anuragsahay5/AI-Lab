#include <bits/stdc++.h>
using namespace std;

set<pair<int, int>> visited;
pair<int, int> jug_capacity = {3, 4};

bool dfsJugSearch(pair<int, int> jug)
{
    if (jug.second == 2)
        return true;

    visited.insert(jug); // store all visited jug states
    vector<pair<int, int>> possible_combs = {
        {jug.first, 0},                                                                                          // empty jug 2
        {jug.first, jug_capacity.second},                                                                        // completly fill jug 2
        {min(jug_capacity.first, jug.first + jug.second), max(jug.first + jug.second - jug_capacity.first, 0)},  // transfer from jug 2 to jug 1
        {0, jug.second},                                                                                         // empty jug 1
        {jug_capacity.first, jug.second},                                                                        // completly fill jug 1
        {max(jug.first + jug.second - jug_capacity.second, 0), min(jug_capacity.second, jug.first + jug.second)} // transfer from jug 1 to jug 2
    };

    bool ans = 0;
    for (pair<int, int> &pr : possible_combs)
    {
        if (visited.find(pr) == visited.end()) // if the current state is not visiited , explore it
        {
            ans |= dfsJugSearch(pr);
            if (ans)
                break;
        }
    }
    return ans;
}

int main()
{

    pair<int, int> jug = {0, 0};
    cout << (dfsJugSearch(jug) == true ? "Possible" : "Not Possible") << endl;
    return 0;
}
