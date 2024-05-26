#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

int nodesProcessed = 0; // Counter to keep track of the number of nodes processed

void printpath(map<pii, pii> mp, pii u)
{
    if (u.first == 0 && u.second == 0)
    {
        cout << 0 << " " << 0 << endl;
        return;
    }
    printpath(mp, mp[u]);
    cout << u.first << " " << u.second << endl;
}

void DFS(int a, int b, int target)
{
    map<pii, int> m;
    bool isSolvable = false;
    map<pii, pii> mp;
    stack<pii> stk;
    stk.push(make_pair(0, 0));
    while (!stk.empty())
    {
        auto u = stk.top();
        stk.pop();
        nodesProcessed++; // Increment the counter for every visited node
        if (m[u] == 1)
            continue;
        if ((u.first > a || u.second > b || u.first < 0 || u.second < 0))
            continue;
        m[{u.first, u.second}] = 1;
        if (u.first == target || u.second == target)
        {
            isSolvable = true;
            printpath(mp, u);
            if (u.first == target)
            {
                if (u.second != 0)
                    cout << u.first << " " << 0 << endl;
            }
            else
            {
                if (u.first != 0)
                    cout << 0 << " " << u.second << endl;
            }
            return;
        }
        // completely fill the jug 2
        if (m[{u.first, b}] != 1)
        {
            stk.push({u.first, b});
            mp[{u.first, b}] = u;
        }
        // completely fill the jug 1
        if (m[{a, u.second}] != 1)
        {
            stk.push({a, u.second});
            mp[{a, u.second}] = u;
        }
        // transfer jug 1 -> jug 2
        int d = b - u.second;
        if (u.first >= d)
        {
            int c = u.first - d;
            if (m[{c, b}] != 1)
            {
                stk.push({c, b});
                mp[{c, b}] = u;
            }
        }
        else
        {
            int c = u.first + u.second;
            if (m[{0, c}] != 1)
            {
                stk.push({0, c});
                mp[{0, c}] = u;
            }
        }
        // transfer jug 2 -> jug 1
        d = a - u.first;
        if (u.second >= d)
        {
            int c = u.second - d;
            if (m[{a, c}] != 1)
            {
                stk.push({a, c});
                mp[{a, c}] = u;
            }
        }
        else
        {
            int c = u.first + u.second;
            if (m[{c, 0}] != 1)
            {
                stk.push({c, 0});
                mp[{c, 0}] = u;
            }
        }
        // empty the jug 2
        if (m[{u.first, 0}] != 1)
        {
            stk.push({u.first, 0});
            mp[{u.first, 0}] = u;
        }
        // empty the jug 1
        if (m[{0, u.second}] != 1)
        {
            stk.push({0, u.second});
            mp[{0, u.second}] = u;
        }
    }
    if (!isSolvable)
        cout << "No solution";
}

int main()
{
    int Jug1, Jug2, target;
    cout << "\nEnter jug 1 capacity : ";
    cin >> Jug1;
    cout << "\nEnter jug 2 capacity : ";
    cin >> Jug2;
    cout << "\nEnter target : ";
    cin >> target;
    cout << "Path from initial state "
            "to solution state ::\n";
    DFS(Jug1, Jug2, target);

    cout << "\nNodes processed: " << nodesProcessed << endl; // Print the number of nodes processed
    return 0;
}
