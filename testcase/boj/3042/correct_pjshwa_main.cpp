#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

// https://wogud6792.tistory.com/12
ll ccw(pll a, pll b, pll c){
  return (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first);
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
char board[MAX + 1][MAX + 1];

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> board[i];

  vector<pll> points;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    if (board[i][j] != '.') points.push_back({i, j});
  }

  int sz = points.size(), ans = 0;
  for (int i = 0; i < sz; i++) for (int j = i + 1; j < sz; j++) for (int k = j + 1; k < sz; k++) {
    if (ccw(points[i], points[j], points[k]) == 0) ans++;
  }

  cout << ans << '\n';
}
