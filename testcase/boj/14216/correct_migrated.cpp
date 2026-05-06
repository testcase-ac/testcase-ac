#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin>>n;
    int a[n+1][n+1];
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) cin>>a[i][j];
    vector<int> u(n+1,0),v(n+1,0),p(n+1,0),w(n+1,0),d(n+1,0);
    for(int i=1;i<=n;i++) {
        p[0]=i;
        int j0=0;
        for(int j=0;j<=n;j++) d[j]=1e9;
        vector<bool> vis(n+1,0);
        do {
            vis[j0]=1;
            int i0=p[j0],j1,mn=1e9;
            for(int j=1;j<=n;j++) if(!vis[j]) {
                int t=a[i0][j]-u[i0]-v[j];
                if(t<d[j]) {d[j]=t;w[j]=j0;}
                if(d[j]<mn) {mn=d[j];j1=j;}
            } for(int j=0;j<=n;j++) {
                if(vis[j]) {u[p[j]]+=mn;v[j]-=mn;}
                else d[j]-=mn;
            } j0=j1;
        } while(p[j0]);
        do {
            int j1=w[j0];
            p[j0]=p[j1];
            j0=j1;
        } while(j0);
    } int r=0;
    for(int j=1;j<=n;j++) r+=a[p[j]][j];
    cout<<r;
}
