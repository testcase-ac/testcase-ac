//제 코드가 너무 느려서 qoj에서 가장 빠른 제출인 eldar님의 #1838839번 제출 코드를 올립니다
#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
//#pragma GCC target("avx2")

using namespace std;
#define Magic ios_base::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
#define all(v) v.begin(),v.end()
#define fori(i, n) for(int i=0;i<(n);++i)
using ll = long long;
using ld = long double;
using vll = vector<ll>;
using vi = vector<int>;
using vvi = vector<vi>;
using vvll = vector<vll>;
using vvvi = vector<vvi>;
using vld = vector<ld>;
using pll = pair<ll, ll>;
using vpll = vector<pll>;

template<class T>
ostream& operator<<(ostream& ost, vector<T>& v){
    ost<<"[";
    for(T& x: v) ost<<x<<" ";
    return ost<<"]\n";
}



ll fpow(ll a, ll b, ll m) {
    ll res = 1 % m;
    for (; b > 0; b >>= 1) {
        if (b & 1)
            res = res * a % m;
        a = (a * a) % m;
    }
    return res;
}

ll N=401;
vll fact;
vll ans;

void precalc(){
    ll p;
    cin >> p;
    fact.assign(N, 1);
    for(int i=1;i<N;i++)
        fact[i]= fact[i - 1] * i % p;
    vvll f(N,vll(N,0));
    ans.assign(N,0);
    ans[1]=1;
    vll g(N,0);
    g[1]=1;
    for(int i=2;i<N;i++){
        for(int j=1;j<i;j++)
            g[i]=(g[i]+g[j]*fact[i-j])%p;
        g[i]=fact[i]-g[i]+p;
        g[i]%=p;
    }
    for(int k=2;k<N;k++){
        vll v(k,0);
        fori(l,k){
            for(ll r=l+1;r<k;r++){
                if(l==0 && r==k-1)
                    continue;
                ll d=r-l+1;
                v[l]+=(f[k-d+1][l]+ans[k-d+1])*(f[d][1]+ans[d])%p;
            }
            v[l]%=p;
        }
        if(k>2)
            v[1]+=2*(p-g[k-2]);
        v[1]%=p;
        for(int i=k-1;i>=0;--i){
            if(i<k-1)
                f[k][i]=f[k][i+1];
            f[k][i]+=v[i];
            f[k][i]%=p;
        }
        ans[k]=(fact[k]+p-f[k][0])%p;
    }
    /*fori(i,N)
        cout << i << " " << ans[i] << endl;
    fori(k,10)
        fori(i,k)
            cout << k << " " << i << " " << f[k][i] << endl;*/
}

void solve() {
    ll n;
    cin >> n;
    cout << ans[n] << "\n";
}


/*
4 998244353
1
4
5
9
*/

int main() {
    int test_count = 1;
    cin >> test_count;
    precalc();
    while (test_count--)
        solve();
}
