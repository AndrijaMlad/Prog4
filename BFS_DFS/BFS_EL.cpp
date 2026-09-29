#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void BFS(int start, vector<pair<int,int>>& e, vector<bool>& vis) 
{
    queue<int> q;
    vis[start] = true;
    q.push(start);
    while (!q.empty()) 
    {
        int node = q.front();
        q.pop();
        cout << node << " ";
        for (auto edge : e) 
        {
            int a = edge.first;
            int b = edge.second;
            if (a == node && !vis[b]) 
            {
                vis[b] = true;
                q.push(b);
            }
            else if (b == node && !vis[a]) 
            {
                vis[a] = true;
                q.push(a);
            }
        }
    }
}

int main() {

    int n = 4;

    vector<pair<int,int>> e = {
        {0,1},
        {0,2},
        {1,3},
        {2,3}
    };

    vector<bool> vis(n, false);

    BFS(0, e, vis);

    return 0;
}