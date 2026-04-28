#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, q; cin >> n >> q;

  vector<pii> A;
  for (int i = 0; i < n; ++i) {
    int x, y; cin >> x >> y;
    A.emplace_back(x, y);
  }

  vector<int> B;
  while (q--) {
    int qx, qy; cin >> qx >> qy;
    B.clear();

    int mdis = 0x3f3f3f3f;
    for (int i = 0; i < n; ++i) {
      auto& [x, y] = A[i];
      int dis = (x - qx) * (x - qx) + (y - qy) * (y - qy);
      if (dis < mdis) {
        mdis = dis;
        B.clear(); B.push_back(i);
      } else if (dis == mdis) {
        B.push_back(i);
      }
    }

    int cnt = B.size();
    if (cnt == 1) cout << "REGION " << B[0] + 1 << '\n';
    else if (cnt == 2) cout << "LINE " << B[0] + 1 << " " << B[1] + 1 << '\n';
    else cout << "POINT\n";
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
