#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 10, INF = 0x3f3f3f3f;
int C[10][10];

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) cin >> C[i][j];

  int ans = -INF;
  for (int s = 0; s < (1 << N); s++) {
    if (__builtin_popcount(s) != K) continue;

    int cur = 0;
    for (int i = 0; i < N; i++) for (int j = i + 1; j < N; j++) {
      if (!(s & (1 << i)) || !(s & (1 << j))) continue;
      cur += C[i][j];
    }
    ans = max(ans, cur);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
