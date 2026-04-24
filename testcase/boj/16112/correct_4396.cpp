#include <bits/stdc++.h>
#define rep(i,n) for(int i=0; i<(n); i++)
#define sz(x) ((int)(x).size())
#define ll long long
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    ll a[n];
    rep(i,n) cin >> a[i];
    sort(a, a+n);
    int mult = 0;
    ll ans = 0;
    for(ll i: a) {
        ans += i*mult;
        if(mult < k) mult++;
    }
    cout << ans;
}
