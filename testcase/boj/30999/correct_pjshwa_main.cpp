#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;

  int ans = 0;
  for (int i = 0; i < N; ++i) {
    string S; cin >> S; int cnt = 0;
    for (int j = 0; j < M; ++j) cnt += S[j] == 'O';
    ans += cnt > M / 2;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
