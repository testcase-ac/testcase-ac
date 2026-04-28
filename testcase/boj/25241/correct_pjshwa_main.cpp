#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 200;
int board[MAX][MAX];

bool adj(int i1, int j1, int i2, int j2) {
  if (abs(i1 - i2) + abs(j1 - j2) == 1) return true;
  if (abs(i1 - i2) == 1 && abs(j1 - j2) == 1) return true;
  return false;
}

void solve() {
  int r, c, n, a[3];
  cin >> r >> c >> n >> a[0] >> a[0] >> a[0] >> a[0] >> a[1] >> a[2];
  
  priority_queue<int> tops;
  for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) cin >> board[i][j], tops.push(board[i][j]);

  vector<int> v;
  for (int i = 0; i < n; i++) {
    v.push_back(tops.top());
    tops.pop();
  }
  sort(v.begin(), v.end());
  int tsum = accumulate(v.begin(), v.end(), 0);

  int ans = 0;
  for (int i1 = 0; i1 < r; i1++) for (int j1 = 0; j1 < c; j1++)
  for (int i2 = 0; i2 < r; i2++) for (int j2 = 0; j2 < c; j2++)
  for (int i3 = 0; i3 < r; i3++) for (int j3 = 0; j3 < c; j3++) {
    if (i1 == i2 && j1 == j2) continue;
    if (i1 == i3 && j1 == j3) continue;
    if (i2 == i3 && j2 == j3) continue;

    int cur = board[i1][j1] + board[i2][j2] + board[i3][j3];
    if (adj(i1, j1, i2, j2)) cur += a[0];
    if (adj(i2, j2, i3, j3)) cur += a[1];
    if (adj(i3, j3, i1, j1)) cur += a[2];

    vector<int> u = {board[i1][j1], board[i2][j2], board[i3][j3]};
    sort(u.begin(), u.end());
    reverse(u.begin(), u.end());
    int t = 3;
    for (int i = 0; i < 3; i++) {
      if (u[i] >= v[t - 1]) cur -= u[i], t--;
    }

    cur += tsum;
    for (int i = 0; i < t; i++) cur -= v[i];
    ans = max(ans, cur);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
