#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll T=1e18;
int main() {
    int t;
    ll p,q,x;
    cin>>t;
    while(t--) {
        cin>>p>>q;
        if(q==1) {
            cout<<T/2<<'\n';
            continue;
        } x=p/q;
        cout<<T/(q*2)*2+(T%(q*2)>=p%q+q*(1-x%2))+(T%(q*2)>=q*(1+x%2)-p%q)<<'\n';
    }
}
