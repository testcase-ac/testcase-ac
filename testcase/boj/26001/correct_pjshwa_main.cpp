#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXW = 10000, MAXH = 1e18;
int P[MAXW];

bool ask(ll x, ll y) {
  cout << "? " << x << " " << y << endl;
  string s; cin >> s;
  return s == "building";
}

void solve() {
  ll W, H; cin >> W >> H;
  iota(P, P + W, 1);
  shuffle(P, P + W, mt19937(chrono::steady_clock::now().time_since_epoch().count()));

  ll minh = 0; int minh_i = 1;
  for (int i = 0; i < W; ++i) {
    if (!ask(P[i], minh + 1)) continue;

    ll l = minh + 1, r = H + 1;
    while (l < r) {
      ll m = (l + r) / 2;
      if (ask(P[i], m)) l = m + 1;
      else r = m;
    }
    minh = l - 1; minh_i = P[i];

    if (minh == H) break;
  }

  cout << "! " << minh_i << " " << minh << endl;
}

int main() {
  // fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
