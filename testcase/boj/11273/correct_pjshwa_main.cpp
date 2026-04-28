#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e4;
map<int, int> D[MAX + 1];
int B[MAX + 1];

void solve() {
  int n;
  cin >> n;
  vector<pii> G(n);
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    G[i] = {x, y};
  }

  int m;
  cin >> m;
  while (m--) {
    int x, y, r;
    cin >> x >> y >> r;

    for (int i = x - r; i <= x + r; i++) {
      if (i < 0 || i > MAX) continue;

      int j = sqrt(r * r - (x - i) * (x - i));
      D[i][max(0, y - j)]++;
      if (y + j <= MAX) D[i][y + j + 1]--;
    }
  }

  int ans = 0, l = -1;
  sort(G.begin(), G.end());
  for (int i = 0; i < n; i++) {
    auto [x, y] = G[i];
    if (x != l) {
      memset(B, 0, sizeof(B));
      B[0] = D[x][0];
      for (int j = 1; j <= MAX; j++) B[j] = B[j - 1] + (D[x].count(j) ? D[x][j] : 0);
      l = x;
    }
    if (B[y] == 0) ans++;
  }

  cout << ans << '\n';

}
 
int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}