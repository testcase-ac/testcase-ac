#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3000;
int B2[MAX + 1], B3[MAX + 1], B4[MAX + 1];
int C2[MAX + 1], C3[MAX + 1], C4[MAX + 1];

void solve() {
  int N, M; cin >> N >> M;

  vector<tuple<int, int, int, int>> D;
  for (int i = 0; i < M; i++) {
    int p, x, q, y; cin >> p >> x >> q >> y;
    D.emplace_back(p, q, x, y);
  }
  sort(D.begin(), D.end());

  ll ans = 0;
  for (int a = 1; a <= N; a++) for (int b = 1; b <= N; b++) for (int c = 1; c <= N; c++) 
  for (int d = 1; d <= N; d++) {
    ans++;
    for (auto& [p, q, x, y] : D) {
      if (p == 1 && q == 2 && x == a && y == b) {
        ans--;
        break;
      }
      if (p == 1 && q == 3 && x == a && y == c) {
        ans--;
        break;
      }
      if (p == 1 && q == 4 && x == a && y == d) {
        ans--;
        break;
      }
      if (p == 2 && q == 3 && x == b && y == c) {
        ans--;
        break;
      }
      if (p == 2 && q == 4 && x == b && y == d) {
        ans--;
        break;
      }
      if (p == 3 && q == 4 && x == c && y == d) {
        ans--;
        break;
      }
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
