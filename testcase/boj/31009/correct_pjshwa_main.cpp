#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<pair<string, int>> A;
  for (int i = 0; i < N; ++i) {
    string S; int C; cin >> S >> C;
    A.emplace_back(S, C);
  }

  int ans = 0;
  for (int i = 0; i < N; ++i) {
    if (A[i].first == "jinju") ans = A[i].second;
  }
  int cnt = 0;
  for (int i = 0; i < N; ++i) {
    if (A[i].second > ans) ++cnt;
  }
  cout << ans << '\n' << cnt << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
