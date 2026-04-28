#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
int C[MAX];

void solve() {
  int N, M, K; cin >> N >> M >> K;
  vector<tii> A(N);
  for (int i = 0; i < N; i++) {
    int x, y; cin >> x >> y;
    A[i] = {x, y, i};
  }

  ll ans = 0, use = 0;
  sort(A.begin(), A.end(), [](tii& a, tii& b) {
    return get<1>(a) > get<1>(b);
  });
  for (int i = 0; i < K; i++) {
    auto& [x, y, idx] = A[i];
    ans += x; C[idx] = 1;
  }

  sort(A.begin(), A.end(), [](tii& a, tii& b) {
    return get<0>(a) > get<0>(b);
  });
  for (int i = 0; i < N; i++) {
    auto& [x, y, idx] = A[i];
    if (C[idx]) continue;
    ans += x; C[idx] = 1; use++;
    if (use == M) break;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
