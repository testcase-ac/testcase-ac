#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;

  int E[N + 1]; memset(E, 0, sizeof(E));
  for (int i = 0; i < M; ++i) {
    int k, s, e; cin >> k >> s >> e;
    if (s >= E[k]) {
      cout << "YES\n";
      E[k] = e;
    }
    else cout << "NO\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
