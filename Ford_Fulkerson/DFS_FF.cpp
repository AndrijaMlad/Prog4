#include <iostream>
#include <stack>
#include <vector>

using namespace std;

const int INF=2e9;

int dfs(int s, int t, vector<vector<int>> &g, vector<int> &dad, vector<vector<int>> &cap)
{
    ///reset to -1
    for(int &v:dad)v=-1;
    dad[s]=-2;
    ///dfs za naogjanje na augmented path
    stack<pair<int,int>> st;
    st.push({s,INF});
    while(!st.empty())
    {
        int v=st.top().first;
        int x=st.top().second;
        st.pop();
        if(v==t)
        {
            return x;
        }
        for(int w:g[v])
        {
            if(cap[v][w]>0&&dad[w]==-1)
            {
                dad[w]=v;
                st.push({w,min(x,cap[v][w])});
            }
        }
    }
    return 0;
}

int ford_fulkerson(int s,int t,vector<vector<int>> &g,vector<vector<int>> cap)
{
    if(s==t)return -1;
    int ans=0;
    vector<int> dad(g.size());
    int x;
    while(x=dfs(s,t,g,dad,cap))///najdi go minimalniot edge na patot od s do t
    {
        ans+=x;
        for(int v=t;v!=s;v=dad[v])///backtracking i odzemi x na edgovite i dodadi x na reverse edgovite
        {
            cap[dad[v]][v]-=x;
            cap[v][dad[v]]+=x;
        }
    }
    return ans;///vrati ja totalnata suma
}


int main()
{
    int n,m;
    cin>>n>>m;
    vector<vector<int>> g(n);
    vector<vector<int>> cap(n,vector<int>(n,0));
    for(int i=0;i<m;i++)
    {
        int x,y,w;
        cin>>x>>y>>w;
        g[x].push_back(y);
        g[y].push_back(x);
        cap[x][y]=w;
    }
    cout<<ford_fulkerson(0,n-1,g,cap)<<endl;
}