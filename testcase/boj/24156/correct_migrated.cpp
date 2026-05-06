#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin>>n;
    int l=1,r=n,x=n;
    vector<pair<int,int>> v;
    for(int i=2;i*i<=x;i++) {
        if(x%i==0) {
            int t=0;
            while(x%i==0) {t++;x/=i;}
            v.push_back({i,t});
        }
    } if(x>1) v.push_back({x,1});
    while(l+1<r) {
        bool f=1;
        int m=l+r>>1;
        for(auto [p,e]:v) {
            int t=m/p,k=0;
            while(t) {
                k+=t;
                t/=p;
            } if(k<e) {f=0;break;}
        } if(f) r=m;
        else l=m;
    } cout<<r;
}
