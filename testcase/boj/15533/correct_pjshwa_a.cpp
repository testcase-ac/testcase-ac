#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define X first
#define Y second
#define SZ(a) ((int)a.size())
#define ALL(v) v.begin(), v.end()
#define pb push_back
 
const int MOD[2] = {998244353, 998244853};
const int P[2] = {100003, 100019};
map<pii, int> cnt;
vector<int> G[100005];
ll ans = 0;
 
pii operator+(const pii &a, const pii &b) { return pii((a.X + b.X) % MOD[0], (a.Y + b.Y) % MOD[1]); }
pii operator*(const pii &a, const pii &b) { return pii((ll)a.X * b.X % MOD[0], (ll)a.Y * b.Y % MOD[1]); }
 
pii dfs(int u, int f) {
    pii sum = pii(1, 1);
    for (int i : G[u])
        if (i != f) {
            pii rt = dfs(i, u);
            sum = sum + pii(P[0], P[1]) * rt;
        }
    ans += cnt[sum], ++cnt[sum];
    return sum;
}
 
int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        G[a].pb(b);
        G[b].pb(a);
    }
    dfs(1, 1);
    cout << ans << "\n";
}
