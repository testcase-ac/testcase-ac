#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5, INF = 1e9 + 7;
int id[MAX], a[4][MAX];
bool vis[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> id[i] >> a[0][i] >> a[1][i] >> a[2][i] >> a[3][i];

  for (int t = 0; t < 4; t++) {
    int ci = -1, cs = -1, cid = INF;
    for (int i = 0; i < n; i++) {
      if (vis[i]) continue;
      if (cs < a[t][i]) {
        cs = a[t][i];
        ci = i;
        cid = id[i];
      }
      else if (cs == a[t][i] && cid > id[i]) {
        cs = a[t][i];
        ci = i;
        cid = id[i];
      }
    }
    cout << cid << ' ';
    vis[ci] = true;
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
