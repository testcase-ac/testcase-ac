#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5000;
pll A[MAX], d[MAX + 1][MAX + 1];

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i].first;
  for (int i = 0; i < N; i++) cin >> A[i].second;
  sort(A, A + N, [] (pll a, pll b) {
    if (a.second == b.second) return a.first > b.first;
    return a.second < b.second;
  });

  d[N][0] = {0, 0};
  for (int i = N - 1; i >= 0; i--) {
    d[i][0] = {0, 0};
    for (int j = 1; j <= N - i; j++) {
      auto [l, v] = d[i + 1][j - 1];
      pll c = {
        l + 1,
        max(v - l * A[i].second + A[i].first, 0LL)
      };
      if (c.second > d[i + 1][j].second || (c.second == d[i + 1][j].second && c.first < d[i + 1][j].first)) d[i][j] = c;
      else d[i][j] = d[i + 1][j];
    }
  }

  ll ans = 0;
  for (int i = 0; i <= N; i++) ans = max(ans, d[0][i].second);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
