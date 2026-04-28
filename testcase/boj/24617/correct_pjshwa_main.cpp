#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500, INF = 1e9 + 7;
int pref[MAX + 1][MAX + 1];
bool reach[MAX + 1][MAX + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cin >> pref[i][j];
  
  for (int i = 1; i <= n; i++) {
    bool w = false;
    for (int j = 1; j <= n; j++) {
      int x = pref[i][j];
      if (!w) reach[i][x] = 1;
      w |= x == i;
    }
  }

  // Floyd-Warshall
  for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
    reach[i][j] |= reach[i][k] && reach[k][j];
  }

  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
    int x = pref[i][j];
    if (reach[x][i]) {
      cout << x << '\n';
      break;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
