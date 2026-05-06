#include <bits/stdc++.h>
using namespace std;
int main() {
    int n,p,k,i=0;
    cin>>n>>p;
    unordered_map<int,int> vis;
    k=(n*n)%p;
    while(vis.find(k)==vis.end()) {
        vis[k]=i++;
        k=(k*n)%p;
    } cout<<i-vis[k];
}
