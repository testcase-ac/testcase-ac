#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void compress(vector<int>& v) {
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
}

const int MAXG = 1e6 + 10;
int G[MAXG + 1];
  
int get_grundy(ll x) {
  vector<int> Gs;
  for (ll y = sqrt(x) + 2;; --y) {
    ll y2 = y * y, y4 = y * y * y * y;
    if (y2 > x || y >= x) continue;
    if (y4 < x) break;
    Gs.push_back(G[y]);
  }
  compress(Gs);

  // calculate mex of Gs
  int mex = 0;
  for (int g : Gs) {
    if (g == mex) ++mex;
  }
  return mex;
}

int get_grundy_v2(ll x) {
  if (x < 4) return 0;
  if (x < 16) return 1;
  if (x < 82) return 2;
  if (x < 6724) return 0;
  if (x < 50626) return 3;
  if (x < 2562991876) return 1;
  return 2;
}

void solve() {
  ll N, ans = 0; cin >> N;
  for (int i = 0; i < N; ++i) {
    ll x; cin >> x;
    ans ^= get_grundy_v2(x);
  }
  if (ans) cout << "koosaga\n";
  else cout << "cubelover\n";
}

int main() {
  fast_io();

  // for (int i = 1; i <= MAXG; ++i) {
  //   G[i] = get_grundy(i);
  //   if (G[i] != G[i - 1]) cout << "G[" << i << "] = " << G[i] << '\n';
  // }
  // ll l = 50700, r = 1e12 + 1;
  // while (l < r) {
  //   ll m = (l + r) / 2;
  //   if (get_grundy(m) == 1) l = m + 1;
  //   else r = m;
  // }
  // cout << l << '\n';

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
