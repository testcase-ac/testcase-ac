#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 3e5;
int H[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> H[i];

  int l = 1, r = N + 1;
  while (l < r) {
    int m = (l + r) / 2;

    int sum = 0, ok = 0;
    for (int j = 0; j < m; ++j) sum += H[j] >= m;
    for (int j = m; j < N; ++j) {
      if (sum == m) {
        ok = 1;
        break;
      }
      sum += (H[j] >= m) - (H[j - m] >= m);
    }
    if (sum == m) ok = 1;

    if (ok) l = m + 1;
    else r = m;
  }
  cout << l - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
