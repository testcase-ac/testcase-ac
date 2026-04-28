#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define MAXN 200010
using namespace std;

int n;
vector<int>g[MAXN];
vector<int>vis(MAXN);
pair<int,int> dfs(int node){
    vis[node]=1;
    int q,w,u,c,x;
    q=w=u=x=c=0;
    pair<int,int>p;
    for(auto it=g[node].begin();it!=g[node].end();it++){
        if(vis[*it]==0){
            p=dfs(*it);
            q+=p.ff;
            if(p.ss==0){
                w++;
            }
            else if(p.ss==1){
                u++;
            }
            else{
                x++;
            }
        }
    }
    int r=0;
    if(w>0){
        w=1;
        r=1;
    }
    else if(u>0){
        w=0;
        r=2;
    }
    else{
        w=0;
        r=0;
    }
    q+=w;
    return mp(q,r);
}

int hospital(int city_nodes, vector<int> city_from, vector<int> city_to) {
  n = city_nodes;
  int m = city_to.size();
  for(int i=0;i<m;i++){
    g[city_from[i]].pb(city_to[i]);
    g[city_to[i]].pb(city_from[i]);
  }
  int r = 0;
  for(int i=0;i<n;i++){
    if (!vis[i + 1]) {
      pair<int,int>ans=dfs(i + 1);
      r += ans.ff;
      if (ans.ss==0) r++;
    }
  }
  return r;
}

int main() {
  int m, x, y;
  cin >> n >> m;

  vector<int> city_from, city_to;
  while (m--) {
    cin >> x >> y;
    city_from.pb(x);
    city_to.pb(y);
  }

  cout << hospital(n, city_from, city_to) << '\n';
}
