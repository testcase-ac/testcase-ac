#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2000;
int send[MAX + 1][MAX + 1];
int carry[MAX + 1];

void solve() {
  int n, c, m;
  cin >> n >> c >> m;
  while (m--) {
    int f, t, w;
    cin >> f >> t >> w;
    send[f][t] += w;
  }

  int cap = 0, ans = 0;
  for (int i = 1; i <= n; i++) {
    cap -= carry[i];

    for (int j = i + 1; j <= n; j++) {
      int w = send[i][j];
      int addend = min(w, c - cap);
      ans += addend;
      cap += addend;
      carry[j] += addend;
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
