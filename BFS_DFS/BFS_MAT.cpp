#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void BFS(int start, vector<vector<int>>& mat, vector<bool>& vis) 
{
    queue<int> q;
    vis[start] = true;
    q.push(start);
    while (!q.empty()) 
    {
        int node = q.front();
        q.pop();
        cout << node << " ";
        int n = mat.size();
        for(int i = 0; i < n; i++) 
        {
            if(mat[node][i] == 1 && !vis[i]) 
            {
                vis[i] = true;
                q.push(i);
            }
        }
    }
}

int main() {

    vector<vector<int>> mat = {
        {0,1,1,0},
        {1,0,0,1},
        {1,0,0,1},
        {0,1,1,0}
    };

    int n = mat.size();
    vector<bool> vis(n, false);
    BFS(0, mat, vis);

    return 0;
}