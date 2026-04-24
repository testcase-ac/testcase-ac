#include <bits/stdc++.h>
using namespace std;
#define int long long
using ld=long double;
ld pi=M_PI;
int h,w;
char M[1000][1000];
vector<pair<int,ld>> D[3000000];
int f(int i, int j){
    return (2*w+1)*i+j;
}
const int Max=3000000;
ld dist[Max];
void dijkstr(int s){
    priority_queue<pair<ld,int>> pq;
    pq.push({0,s});
    dist[s]=0;
    while(!pq.empty()){
        ld cost=-pq.top().first;
        int here=pq.top().second;
        pq.pop();
        if(dist[here]<cost) continue;
        for(int i=0;i<D[here].size();++i){
            ld via_cost=cost+D[here][i].second;
            if(via_cost<dist[D[here][i].first]){
                dist[D[here][i].first]=via_cost;
                pq.push({-via_cost,D[here][i].first});
            }
        }
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);   
    cin>>h>>w;
    for(int i=0;i<h;++i){
        for(int j=0;j<w;++j){
            cin>>M[i][j];
            if(M[i][j]=='O'){
                int u=f(2*i,2*j+1);
                int l=f(2*i+1,2*j);
                int r=f(2*i+1,2*j+2);
                int d=f(2*i+2,2*j+1);
                D[u].push_back({r,(ld)2.5*pi});
                D[r].push_back({u,(ld)2.5*pi});
                D[u].push_back({l,(ld)2.5*pi});
                D[l].push_back({u,(ld)2.5*pi});
                D[r].push_back({d,(ld)2.5*pi});
                D[d].push_back({r,(ld)2.5*pi});
                D[d].push_back({l,(ld)2.5*pi});
                D[l].push_back({d,(ld)2.5*pi});
            }
        }
    }
    for(int i=0;i<=2*h;++i){
        for(int j=0;j<=2*w;++j){
            int now=f(i,j);
            int r=f(i,j+1);
            int d=f(i+1,j);
            if(i%2==0&&j!=2*w) D[now].push_back({r,5});
            if(j%2==0&&i!=2*h) D[now].push_back({d,5});
        }
    }
    int last=f(2*h,2*w);
    for(int i=0;i<=last;++i){
        dist[i]=1000000000;
    }
    dijkstr(0);
    cout<<fixed;
    cout.precision(12);
    cout<<dist[last];
}
