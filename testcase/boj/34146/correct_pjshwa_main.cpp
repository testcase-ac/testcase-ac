#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 1e4;
int C[MAXV + 1];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    int x; cin >> x;
    ++C[x];
  }

  int odd = 0, ans;
  for (int x = 1; x <= MAXV; ++x) odd += (C[x] & 1);
  if (M & 1) {
    ans = (odd <= N);
  } else {
    ans = (odd == 0);
  }
  cout << (ans ? "YES" : "NO") << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
