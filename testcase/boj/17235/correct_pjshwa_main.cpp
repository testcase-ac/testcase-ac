#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll INF = 1e18;

void solve() {
  int N; cin >> N;
  ll ulmax = -INF, ulmin = INF, llmax = -INF, llmin = INF;
  for (int i = 0; i < N; ++i) {
    ll x, y; cin >> x >> y;
    ulmax = max(ulmax, x + y); ulmin = min(ulmin, x + y);
    llmax = max(llmax, x - y); llmin = min(llmin, x - y);
  }

  __int128_t L = max(ulmax - ulmin, llmax - llmin);
  L *= L;
  cout << (ll)(L / 2);
  if (L % 2) cout << ".5";
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
