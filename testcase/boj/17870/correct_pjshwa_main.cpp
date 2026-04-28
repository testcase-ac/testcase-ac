#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e7;
ll D[MAX + 1];

void solve() {
  int N;
  cin >> N;

  set<ll> u;
  for (int i = 0; i < N; i++) {
    ll x;
    cin >> x;
    for (ll l = 2; l * l <= x; l++) {
      if (x % l == 0) {
        u.insert(l);
        u.insert(x / l);
      }
    }
  }

  int it = 0;
  for (ll e : u) {
    cout << e << ' ';
    if (++it % 5 == 0) cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
