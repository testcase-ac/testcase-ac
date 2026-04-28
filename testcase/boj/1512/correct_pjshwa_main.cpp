#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int M; string S; cin >> M >> S;
  int N = S.size();

  int ans = INF;
  for (int i = 1; i <= M; i++) {
    map<char, int> C[M];
    for (int j = 0; j < N; j++) {
      C[j % i][S[j]]++;
    }

    int cur = 0;
    for (int j = 0; j < M; j++) {
      int c_sum = 0, c_max = 0;
      for (auto [c, cnt] : C[j]) {
        c_sum += cnt;
        c_max = max(c_max, cnt);
      }
      cur += c_sum - c_max;
    }
    ans = min(ans, cur);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
