#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5e6;
int N1, N2; ll ans;
int C[MAX + 1];

void dfs1(int i, int val) {
  if (i == N1) return C[val]++, void();
  for (int d = 0; d < 10; d++) {
    if (i == 0 && d == 0) continue;
    dfs1(i + 1, val * d);
  }
}

void dfs2(int i, int val) {
  if (i == N2) return ans += C[val], void();
  for (int d = 0; d < 10; d++) dfs2(i + 1, val * d);
}

void solve() {
  int N; cin >> N;
  N1 = (N + 1) / 2, N2 = N - N1;
  dfs1(0, 1); dfs2(0, 1);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
