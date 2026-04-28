#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 3e5;
vector<int> D[MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) D[i].clear();

  for (int i = 0; i < N - 1; ++i) {
    int u, v, w; cin >> u >> v >> w;
    D[u].push_back(w); D[v].push_back(w);
  }

  ll ans = 0;
  for (int i = 1; i <= N; ++i) {
    ll msum = 0; int mmax = 0;
    for (int e : D[i]) msum += e, mmax = max(mmax, e);

    if (2 * mmax > msum) ans += 2 * mmax - msum;
    else ans += msum % 2;
  }

  cout << ans / 2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
