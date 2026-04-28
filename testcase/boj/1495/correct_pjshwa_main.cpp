#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 50, MAXV = 1000;
bool d[MAX + 1][MAXV + 1];

void solve() {
  int N, S, M; cin >> N >> S >> M;

  d[0][S] = true;
  for (int i = 1; i <= N; i++) {
    int x; cin >> x;
    for (int v = 0; v <= M; v++) {
      if (v >= x && d[i - 1][v - x]) d[i][v] = true;
      if (v + x <= M && d[i - 1][v + x]) d[i][v] = true;
    }
  }

  int ans = -1;
  for (int v = 0; v <= M; v++) {
    if (d[N][v]) ans = v;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
