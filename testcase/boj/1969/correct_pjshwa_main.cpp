#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int N, M; cin >> N >> M;
  vector<string> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];

  int ans = 0;
  for (int j = 0; j < M; j++) {
    map<char, int> t;
    for (int i = 0; i < N; i++) {
      for (char c : {'A', 'C', 'G', 'T'}) {
        if (c == A[i][j]) continue;
        t[c]++;
      }
    }

    int cnt = INF; char val;
    for (char c : {'A', 'C', 'G', 'T'}) {
      int v = t[c];
      if (v < cnt) cnt = v, val = c;
    }
    cout << val; ans += cnt;
  }
  cout << '\n' << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
