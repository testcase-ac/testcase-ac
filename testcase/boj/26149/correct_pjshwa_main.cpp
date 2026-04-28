#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;

  vector<int> A(N), B(N);
  for (int i = 0; i < N; i++) cin >> A[i];
  for (int i = 0; i < N; i++) cin >> B[i];

  vector<pii> ops;

  sort(A.begin() + 1, A.end(), greater<int>());
  for (int i = 1; i < N; i++) {
    if (A[i]) ops.push_back({1, A[i]});
  }

  vector<pii> P(N - 1);
  for (int i = 1; i < N; i++) P[i - 1] = {B[i], i + 1};

  sort(P.begin(), P.end());
  for (int i = 0; i < N - 1; i++) {
    if (P[i].first) ops.push_back({P[i].second, P[i].first});
  }

  cout << ops.size() << '\n';
  for (auto [a, b] : ops) cout << "+ " << a << ' ' << b << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
