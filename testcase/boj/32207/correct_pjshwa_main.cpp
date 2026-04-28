#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXL = 21;
vector<tuple<int, int, int>> A, cur;
int L, K, ans = 0;

void dfs(int i, int c) {
  if (i == L) {
    int ok = 1, val = 0;
    for (auto& [x1, r1, c1] : cur) {
      val += x1;
      for (auto& [x2, r2, c2] : cur) {
        if (abs(r1 - r2) + abs(c1 - c2) == 1) ok = 0;
      }
    }
    if (ok) ans = max(ans, val);
  } else {

    // choose or not choose
    if (c < K) {
      cur.push_back(A[i]);
      dfs(i + 1, c + 1);
      cur.pop_back();
    }
    dfs(i + 1, c);
  }
}

void solve() {
  int N, M; cin >> N >> M >> K;

  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    int x; cin >> x; A.emplace_back(x, i, j);
  }
  sort(A.begin(), A.end(), greater<>());
  L = min(MAXL, N * M);

  dfs(0, 0);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
