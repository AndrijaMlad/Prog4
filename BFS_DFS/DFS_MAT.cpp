#include <iostream>
#include <vector>
using namespace std;

void DFS(int node, vector<vector<int>>& mat, vector<bool>& vis) 
{
    vis[node] = true;
    cout << node << " ";
    int n = mat.size();
    for(int i = 0; i < n; i++) 
    {
        if(mat[node][i] == 1 && !vis[i]) 
        {
            DFS(i, mat, vis);
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
    DFS(0, mat, vis);

    return 0;
}