#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;

  vector<ll> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];
  while (M--) {
    ll x, b = 0; cin >> x;
    for (int i = 0; i < N; ++i) {
      ll e = min(x, A[i]);
      if (e <= b) continue;

      A[i] += e - b;
      b = e;
      if (b == x) break;
    }
  }

  for (int i = 0; i < N; ++i) cout << A[i] << " \n"[i == N - 1];
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
