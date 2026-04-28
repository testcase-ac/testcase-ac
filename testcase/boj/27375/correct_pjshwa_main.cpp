#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, k; cin >> n >> k;
  vector<tuple<int, int, int>> A;
  for (int i = 0; i < n; i++) {
    int w, s, e; cin >> w >> s >> e;
    A.emplace_back(w, s, e);
  }

  int ans = 0;
  for (int state = 0; state < (1 << n); state++) {
    int P[51]{};

    bool f = true;
    for (int i = 0; i < n; i++) {
      if (!(state & (1 << i))) continue;

      auto [w, s, e] = A[i];
      if (w == 5) {
        f = false;
        break;
      }
      for (int j = w * 10 + s; j <= w * 10 + e; j++) P[j]++;
    }

    int cnt = 0;
    for (int i = 1; i <= 50; i++) {
      if (P[i] > 1) {
        f = false;
        break;
      }
      cnt += P[i];
    }
    if (f) ans += cnt == k;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
