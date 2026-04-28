#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int Y1[MAXN + 1], Y2[MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) {
    int x, y, a; cin >> x >> y >> a;
    a == 1 ? ++Y1[y] : ++Y2[y];
  }

  int ans = 0;
  for (int y = 0; y < MAXN; ++y) {
    int ycnt = Y1[y] + Y2[y], rem = 0;
    while (ycnt > 0 && Y2[y + 1] > 0) {
      --ycnt; --Y2[y + 1]; ++rem;
      ++ans;
    }
    while (ycnt > 0 && Y1[y + 1] > 0) {
      --ycnt; --Y1[y + 1];
      ++ans;
    }
    Y1[y + 1] += rem;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
