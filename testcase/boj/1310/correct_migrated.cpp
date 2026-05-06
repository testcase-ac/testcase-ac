#include <bits/stdc++.h>
#define ll long long
using namespace std;
struct pt {
    ll x,y;
};
vector<pt> p,v;
ll ccw(pt p1,pt p2,pt p3) {
    return p1.x*p2.y+p2.x*p3.y+p3.x*p1.y-p2.x*p1.y-p3.x*p2.y-p1.x*p3.y;
}
bool mn(pt p1,pt p2){
    if(p1.x==p2.x) return p1.y<p2.y;
    else return p1.x<p2.x;
}
bool comp(pt p1,pt p2){
    ll x=ccw(p[0],p1,p2);
    if(x==0) return (p1.x+p1.y)<(p2.x+p2.y);
    else return x>0;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    p.resize(n);
    for(int i=0;i<n;i++) cin>>p[i].x>>p[i].y;
    sort(p.begin(),p.end(),mn);
    sort(p.begin()+1,p.end(),comp);
    v.push_back(p[0]);
    v.push_back(p[1]);
    for(int i=2;i<n;i++) {
        while(v.size()>1) {
            pt p2=v.back();
            v.pop_back();
            pt p1=v.back();
            if(ccw(p1,p2,p[i])>0) {
                v.push_back(p2);
                break;
            }
        } v.push_back(p[i]);
    } ll m=0;
    for(int i=0;i<v.size();i++) {
        for(int j=i+1;j<v.size();j++) {
            pt p=v[i],q=v[j];
            m=max(m,(p.x-q.x)*(p.x-q.x)+(p.y-q.y)*(p.y-q.y));
        }
    } cout<<m;
}
