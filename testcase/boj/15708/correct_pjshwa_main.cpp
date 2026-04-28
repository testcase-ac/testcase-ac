#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, T, P; cin >> N >> T >> P;
  vector<int> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];

  ll l = 1, r = N + 1;
  while (l < r) {
    ll m = (l + r) / 2;

    priority_queue<int> pq; ll acc = 0;
    for (int i = 0; i < m; ++i) {
      pq.push(A[i]);
      acc += A[i];
    }

    bool f = acc + (m - 1) * P <= T;
    for (int i = m; i < N; ++i) {
      pq.push(A[i]); acc += A[i];
      acc -= pq.top(); pq.pop();
      f |= acc + i * P <= T;
    }

    if (f) l = m + 1;
    else r = m;
  }

  cout << l - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
