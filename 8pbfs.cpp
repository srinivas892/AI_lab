#include <bits/stdc++.h>
#include <vector>
#include <queue>
using namespace std;

void findEmpty(vector<vector<int>> board, int &x, int &y)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
        {
            if (board[i][j] == 0)
            {
                x = i;
                y = j;
                return;
            }
        }
    }
}

bool isGoalState(vector<vector<int>> &board, vector<vector<int>> &goal)
{
    return board == goal;
}

int heuristics(vector<vector<int>> &board, vector<vector<int>> &goal)
{
    int h = 0;
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
        {
            if (board[i][j] != goal[i][j])
            {
                h++;
            }
        }
    }
    return h;
}

void printBoard(vector<vector<int>> board)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void solve(vector<vector<int>> &board, vector<vector<int>> &goal, int depth, int x, int y)
{
    priority_queue<pair<int, vector<vector<int>>>, vector<pair<int, vector<vector<int>>>>,
                   greater<pair<int, vector<vector<int>>>>> pq;

    int h = heuristics(board, goal);
    pq.push({h, board});

    while (!pq.empty())
    {
        vector<vector<int>> current = pq.top().second;
        pq.pop();
        depth++;
        printBoard(current);
        int x, y;
        findEmpty(current, x, y);
        if (isGoalState(current, goal))
        {
            cout << "Goal state reached" << endl;
            cout << "Depth: " << depth << endl;
            cout << "Cost: " << depth - 1 << endl;
            return;
        }

        // right, left, up, down
        int dx[] = {0, 0, -1, 1};
        int dy[] = {1, -1, 0, 0};
        for (int i = 0; i < 4; i++)
        {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (newX >= 0 && newX < current.size() && newY >= 0 && newY < current.size())
            {
                swap(current[x][y], current[newX][newY]);
                h = heuristics(current, goal);
                pq.push({h, current});
                swap(current[newX][newY], current[x][y]);
            }
        }
    }
    cout << "Goal state not reached" << endl;
    return;
}

int main()
{
    vector<vector<int>> initial = {{2, 8, 3},
                                    {1, 6, 4},
                                    {7, 0, 5}};
   cout<<"enter the initial state";
  for(int i=0 ;i <3; i++){
    for(int j  = 0; j<3; j++)
            cin>>initial[i][j];
  }

    vector<vector<int>> goal = {{1, 2, 3},
                                 {8, 0, 4},
                                 {7, 6, 5}};
    int x, y;
    cout << "8 Puzzle Problem using Best First Search -"<< endl;
    cout << "Initial State - " << endl;
    findEmpty(initial, x, y);
    solve(initial, goal, 0, x, y);

    return 0;
}