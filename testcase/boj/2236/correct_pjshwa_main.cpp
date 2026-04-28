#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K;
  cin >> N >> K;

  vector<pii> A(N);
  for (int i = 0; i < N; i++) {
    int v; cin >> v;
    A[i] = {v, i + 1};
  }
  sort(A.begin(), A.end(), greater<pii>());

  vector<int> ans(N + 1, 0);
  for (int i = 0; i < K; i++) {
    if (i >= N) {
      cout << "0\n";
      continue;
    }

    auto [_, x] = A[i];
    cout << x << '\n';
    ans[x] = x;
  }

  for (int i = 1; i <= N; i++) cout << ans[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
