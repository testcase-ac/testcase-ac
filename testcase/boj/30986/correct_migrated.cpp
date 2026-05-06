#include <bits/stdc++.h>
using namespace std;
vector<int> g[17];
bool vis[17];
int v[17];
bool dfs(int n) {
    if(vis[n]) return 0;
    vis[n]=1;
    int x=g[n].size();
    for(int i=0;i<x;i++) {
        int a=g[n][i];
        if(!v[a]||dfs(v[a])) {
            v[a]=n;
            return 1;
        }
    } return 0;
}
int main() {
    g[1]={2,3,4,5};
    g[6]={2,3,12,13};
    g[7]={2,4,12,14};
    g[8]={2,5,13,14};
    g[9]={3,4,12,15};
    g[10]={3,5,13,15};
    g[11]={4,5,14,15};
    g[16]={12,13,14,15};
    int n,a,b,k=0;
    cin>>n;
    while(n--) {
        cin>>a>>b;
        if((a>1&&a<6)||(a>11&&a<16)) swap(a,b);
        g[a].erase(find(g[a].begin(),g[a].end(),b));
    } for(int i=1;i<=16;i++) {
        memset(vis,0,sizeof(vis));
        if(dfs(i)) k++;
    } cout<<16-k;
}
