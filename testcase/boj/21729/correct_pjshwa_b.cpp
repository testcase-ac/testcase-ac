#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 1000003;

ll mpow(ll x, ll y){
    if(!y) return 1;
    if(y&1) return mpow(x, y-1) * x % MOD;
    ll tmp = mpow(x, y/2);
    return tmp*tmp%MOD;
}

inline ll modInv(ll x){
    return mpow(x, MOD-2);
}

struct modInt {
    ll val;

    /// 생성자, 소멸자
    modInt(){
        val = 0;
    }
    modInt (ll _v){
        val = _v;
    }
    ~modInt (){}

    /// 사칙연산
    modInt operator+(const modInt &r)const{
        return (val + r.val) % MOD;
    }
    modInt operator-(const modInt &r)const{
        return (val - r.val + MOD) % MOD;
    }
    modInt operator*(const modInt &r)const{
        return val * r.val % MOD;
    }
    modInt operator/(const modInt &r)const{
        return val * modInv(r.val) % MOD;
    }
};

namespace calculateNcK{
    modInt fact[1000009], factInv[1000009];
    void init(){
        fact[0] = 1;
        for(int i=1; i<MOD; i++) fact[i] = fact[i-1] * i;
        factInv[MOD-1] = modInt(1) / fact[MOD-1];
        for(int i=MOD-2; i>=0; i--) factInv[i] = factInv[i+1] * (i+1);
    }

    ll nCk(ll x, ll y){
        if(!x || !y) return 1;
        ll xk = x%MOD, yk = y%MOD;
        if(xk < yk) return 0;
        return (fact[xk] * factInv[yk] * factInv[xk-yk]).val * nCk(x/MOD, y/MOD) % MOD;
    }
}

ll nCk(ll x, ll y){
    if(x>0) return calculateNcK::nCk(x, y);
    ll ret = calculateNcK::nCk(-x+y-1, y);
    if(y%2) ret = (MOD - ret) % MOD;
    return ret;
}

ll funcP(ll j){
    return j * (j*3-1) / 2;
}

ll solve(ll n, ll k){
    ll ans = 0;
    for(ll j=0; funcP(j) <= k; j++) ans += nCk(-n, k-funcP(j)) * ((j+k-funcP(j))%2 ? -1 : 1);
    for(ll j=-1; funcP(j) <= k; j--) ans += nCk(-n, k-funcP(j)) * ((j+k-funcP(j))%2 ? -1 : 1);
    if(ans >= 0) ans %= MOD;
    else ans = (MOD - (-ans % MOD)) % MOD;
    return ans;
}

int main(){
    calculateNcK::init();
    int t;
    scanf("%d", &t);
    while(t--){
        ll n, k;
        scanf("%lld %lld", &n, &k);
        if(k<=n) printf("%lld\n", solve(n, k));
        else printf("%lld\n", (solve(n, k) + solve(n+1, k-n-1))%MOD);
    }
}

