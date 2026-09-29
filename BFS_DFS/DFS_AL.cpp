#include <iostream>
#include <vector>
using namespace std;

void DFS(int node, vector<vector<int>>& g, vector<bool>& vis) {
    vis[node] = true;
    cout << node << " ";
    for (int ax : g[node]) 
    {
        if (!vis[ax]) {
            DFS(ax, g, vis);
        }
    }
}

int main() {
    int n = 4;

    vector<vector<int>> g(n);

    g[0] = {1, 2};
    g[1] = {0, 3};
    g[2] = {0, 3};
    g[3] = {1, 2};

    vector<bool> vis(n, false);

    DFS(0, g, vis);

    return 0;
}
