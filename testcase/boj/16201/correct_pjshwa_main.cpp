#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1e9 + 7;
ll tc = 0, tw = 1;
int r, c;

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

void adiff(int diff) {
  if (diff & 1) {
    tc += (diff - 1) / 2;
    tw = (tw * (diff + 1) / 2) % MOD;
  }
  else tc += diff / 2;
}

void arow(int rcnt) {
  tc += (ll)rcnt * (c / 2);
  if (c & 1) tw = (tw * lpow((c + 1) / 2, rcnt, MOD)) % MOD;
}

void solve() {
  int n;
  cin >> r >> c >> n;

  vector<pii> tiles(n);
  for (int i = 0; i < n; i++) cin >> tiles[i].first >> tiles[i].second;
  sort(tiles.begin(), tiles.end());

  int lr = 1, lc = 0;
  for (auto& [cr, cc] : tiles) {
    if (lr != cr) {
      adiff(c - lc);
      arow(cr - lr - 1);
      lc = 0, lr = cr;
    }
    adiff(cc - lc - 1);
    lc = cc;
  }
  if (lr != r) {
    adiff(c - lc);
    arow(r - lr - 1);
    lc = 0, lr = r;
  }
  adiff(c - lc);

  cout << tc << ' ' << tw << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
