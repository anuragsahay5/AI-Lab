#include <bits/stdc++.h>
using namespace std;

void print(set<int> &st)
{
    for (auto &x : st)
    {
        cout << x << " ";
    }
}

int main()
{
    set<int> travelTimes = {1, 3, 6, 8, 12};
    int timeElp = 0;
    set<int> left = travelTimes, right;
    int onLeft = 1;
    
    cout << "Time: " << timeElp << "s,";
    cout << "Left bank: ";
    print(left);
    cout << "Right bank: ";
    print(right);

    right.insert(*left.begin());
    left.erase(left.begin());
    right.insert(*left.begin());
    timeElp += *left.begin();
    left.erase(left.begin());
    onLeft = 1 - onLeft;

    while (1)
    {
        cout << "Time: " << timeElp << "s,";
        cout << "Left bank: ";
        print(left);
        cout << "Right bank: ";
        print(right);
        if (left.size() == 0)
            break;

        if (onLeft)
        {
            right.insert(*left.begin());
            timeElp += *left.begin();
            left.erase(left.begin());
            if (left.size() > 1)
            {
                right.insert(*(--left.end()));
                left.erase(*(--left.end()));
                timeElp += *left.begin();
            }
        }
        else
        {
            left.insert(*right.begin());
            timeElp += *right.begin();
            right.erase(right.begin());
        }
        onLeft = 1 - onLeft;
    }

    return 0;
}