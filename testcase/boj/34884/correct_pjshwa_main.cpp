#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1.5e5;
int A[MAXN];

void solve() {
  int N = MAXN;

  queue<pii> Q;
  Q.emplace(0, N - 1); int v = N;
  while (!Q.empty()) {
    auto [l, r] = Q.front(); Q.pop();
    if (l > r) continue;
    int m = (l + r) / 2;
    A[m] = v--;
    if (m - l > r - m) {
      Q.emplace(l, m - 1);
      Q.emplace(m + 1, r);
    } else {
      Q.emplace(m + 1, r);
      Q.emplace(l, m - 1);
    }
  }

  // ll sum = 0;
  // for (int i = 0; i < N; ++i) for (int j = i; j < N; ++j) {
  //   int v = 0;
  //   for (int k = i; k <= j; ++k) v = max(v, A[k]);
  //   sum += v;
  // }
  // cout << sum << '\n';

  for (int i = 0; i < N; ++i) cout << A[i] << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
