#include <iostream>
#include <vector>
using namespace std;

void DFS(int node, vector<pair<int,int>>& e, vector<bool>& vis)
{
    vis[node] = true;
    cout << node << " ";
    for(auto edge : e)
    {
        int a = edge.first;
        int b = edge.second;
        if(a == node && !vis[b])
        {
            DFS(b, e, vis);
        }
        else if(b == node && !vis[a])
        {
            DFS(a, e, vis);
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

    DFS(0, e, vis);

    return 0;
}
