#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;

  cout << N / 2 + M / 2 << '\n';
  for (int i = 2; i <= N; i += 2) cout << i << ' ' << 1 << ' ' << i << ' ' << M << '\n';
  for (int i = 2; i <= M; i += 2) cout << 1 << ' ' << i << ' ' << N << ' ' << i << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
