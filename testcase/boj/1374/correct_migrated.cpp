#include <bits/stdc++.h>
using namespace std;
int main() {
    int n,a,r=1;
    priority_queue<int,vector<int>,greater<int>> pq;
    cin>>n;
    vector<pair<int,int>> v(n);
    for(int i=0;i<n;i++) cin>>a>>v[i].first>>v[i].second;
    sort(v.begin(),v.end());
    pq.push(v[0].second);
    for(int i=1;i<n;i++) {
        while(!pq.empty()&&pq.top()<=v[i].first) pq.pop();
        pq.push(v[i].second);
        r=max(r,(int)pq.size());
    } cout<<r;
}
