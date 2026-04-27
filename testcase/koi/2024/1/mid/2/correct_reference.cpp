#include <vector>
#include <iostream>
 
using namespace std;
 
typedef long long ll;
 
const int MAXN = 2e5+10;
 
vector<int> pos;
 
ll psum[MAXN];
ll solve(int L, int R) {
 
    if(R <= (L + 1)) return 0LL;
 
    int k = (R - L);
 
    int kk = (k + 1)>>1;
 
    ll tot = psum[R-1]-psum[L-1];
    ll v = psum[L+kk-1]-psum[L-1];
 
    ll mnv = 1LL*pos[L+kk-1]*kk - v;
    mnv += (tot-v) - 1LL*pos[L+kk-1]*(k-kk);
 
    ll Lv = tot - 1LL*pos[L]*k;
    ll Rv = 1LL*pos[R-1]*k - tot;
    
    ll res = max(Lv, Rv)-mnv;
 
    return res;
}
 
int main()
{
    int n, q;
    int x;
    int a, b;
 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin>>n>>q;
 
    pos.push_back(0);
 
    for(int i = 0; i < n; i++) {
        cin>>x;
        pos.push_back(x);
    }
 
    pos.push_back(1000000010);
 
    int psz = (int)pos.size();
 
    for(int i = 1; i < psz; i++) {
        psum[i] = psum[i-1] + (ll)pos[i];
    }
 
    int idx = 0, idy = 0;
    ll res = 0;
 
    for(int i = 0; i < q; i++) {
        cin>>a>>b;
 
        idx = lower_bound(pos.begin(), pos.end(), a)-pos.begin();
        idy = lower_bound(pos.begin(), pos.end(), b+1)-pos.begin();
 
        res = solve(idx, idy);
 
        cout<<res<<"\n";
    }
 
 
    return 0;
}
