#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 35, MAXL = 2e5, LIM = 1e18;
ll d[MAX + 1][MAXL + 1];

ll f(int i, int j) {
  if (i > 35) return LIM + 1;
  return d[i][j];
}

void solve() {
  ll N, K;
  cin >> N >> K;
  N = (N - 2) / 2;

  if (N == 0) {
    if (K == 1) cout << "AD\n";
    else cout << "-1\n";
    return;
  }
  if (K > f(N, N + 1)) return cout << "-1\n", void();

  cout << 'A';
  int i = N, j = N + 1;
  while (j > 1) {
    if (K <= f(i, j)) {
      cout << 'A';
      i--;
    }
    else {
      cout << 'D';
      K -= f(i, j--);
    }
  }
  cout << "D\n";
}

int main() {
  fast_io();

  d[1][0] = 1;
  for (int i = 1; i <= MAX; i++) {
    for (int j = i; j <= MAXL; j++) {
      d[i][j] = d[i - 1][j] + d[i][j - 1];
      if (d[i][j] > LIM) d[i][j] = LIM + 1;
    }
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
