#include <bits/stdc++.h>
#define ll long long
using namespace std;
int main() {
    ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
    vector<ll> p,pw35={15,27,125,225,405,729,1875,3375,6075,10935,15625,19683,28125,50625,91125,164025};
    for(ll i=1;i<167219;i++) {
        if(i%3!=0&&i%5!=0) p.push_back(i);
    } for(ll i=0;i<16;i++) {
        for(ll x=1;x*pw35[i]<167219;x++) {
            if(x%3!=0&&x%5!=0) p.push_back(x*pw35[i]);
        }
    } sort(p.begin(),p.end());
    ll t,n;
    cin>>t;
    while(t--) {
        cin>>n;
        cout<<p[n-1]<<'\n';
    }
}
