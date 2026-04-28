#include <bits/stdc++.h>
using namespace std; typedef long long ll;
void OJize(){cin.tie(NULL); ios_base::sync_with_stdio(false);}

ll modpow(ll a, ll x, ll mod){
    a%= mod; ll r;
    for(r=1; x; x>>=1){if(x&1) r = r*a%mod; a = a*a%mod;}
    return r;
}

const ll MOD = 1000000007;
int main(){OJize();
    ll n, m; cin>>n>>m;
    int sz = max(n, m)+1;
    vector<bool> prime(sz, true);
    prime[0] = prime[1] = false;
    for(int p=2; p<10000 && p<sz; p++){
        if(!prime[p]) continue;
        for(int q=p*p; q<sz; q+=p) prime[q] = false;
    }

    ll ans = 1;
    for(int p=2; p<sz; p++) if(prime[p]){
        ll cnt = 0;
        for(ll x=p; x<sz; x*=p) cnt+= (n/x) * (m/x);
        ans = (ans * modpow(p, cnt, MOD)) % MOD;
    }
    cout << ans;
}
