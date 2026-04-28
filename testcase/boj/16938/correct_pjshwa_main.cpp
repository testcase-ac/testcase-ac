#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 15, INF = 0x3f3f3f3f;
int A[MAX];

void solve() {
  int N, L, R, X;
  cin >> N >> L >> R >> X;
  for (int i = 0; i < N; i++) cin >> A[i];

  int ans = 0;
  for (int state = 1; state < (1 << N); state++) {
    int cnt = __builtin_popcount(state);
    if (cnt < 2) continue;

    int sum = 0, mn = INF, mx = 0;
    for (int i = 0; i < N; i++) {
      if (state & (1 << i)) {
        sum += A[i];
        mn = min(mn, A[i]);
        mx = max(mx, A[i]);
      }
    }

    if (L <= sum && sum <= R && mx - mn >= X) ans++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
