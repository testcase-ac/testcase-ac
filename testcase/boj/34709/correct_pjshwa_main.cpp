#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5e5;
int deg[MAXN];

void solve() {
  int N, sum = 0; cin >> N;
  for (int i = 0; i < N - 1; ++i) {
    int u, v; cin >> u >> v; --u; --v;
    ++deg[u]; ++deg[v];
  }
  for (int i = 0; i < N; ++i) sum += max(0, deg[i] - 2);
  cout << sum << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
