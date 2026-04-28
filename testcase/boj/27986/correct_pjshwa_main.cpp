#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;

  int len = 0x3f3f3f3f;
  for (int i = 0; i < M; i++) {
    int L, R; cin >> L >> R;
    len = min(len, R - L + 1);
  }

  vector<int> ans(N);
  for (int i = 0; i < N; i++) ans[i] = i % len;
  for (int i = 0; i < N; i++) cout << (ans[i] + 1) << " \n"[i == N - 1];
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
