#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 1000;

vector<int> g[MAXN];
bool vis[MAXN];

void BFS(int start) 
{
    queue<int> q;
    vis[start] = true;
    q.push(start);
    while(!q.empty()) 
    {
        int v = q.front();
        q.pop();
        cout << v << " ";
        for(auto u : g[v]) 
        {
            if (!vis[u]) 
            {
                vis[u] = true;
                q.push(u);
            }
        }
    }
}