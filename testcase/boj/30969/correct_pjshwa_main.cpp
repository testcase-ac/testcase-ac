#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  int T[1002]; memset(T, 0, sizeof(T));

  int ans = 0;
  for (int i = 0; i < N; ++i) {
    string S; ll C; cin >> S >> C;
    if (S == "jinju") ans = C;
    T[min(C, 1001LL)]++;
  }

  int cnt = 0;
  for (int j = ans + 1; j <= 1001; ++j) {
    cnt += T[j];
  }
  cout << ans << '\n' << cnt << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
