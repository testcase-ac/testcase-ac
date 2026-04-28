#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int r, c;
int board[300][300], mheights[300][300];

void solve(int tc) {
  priority_queue<pair<int, pair<int, int>>> pq;
  cin >> r >> c;
  for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) cin >> board[i][j], pq.push({board[i][j], {i, j}});
  memset(mheights, 0, sizeof(mheights));

  ll t = 0;
  while (!pq.empty()) {
    auto [h, pos] = pq.top();
    auto [i, j] = pos;
    pq.pop();

    if (board[i][j] > h) continue;
    t += (h - board[i][j]);
    board[i][j] = h;

    if (i > 0 && h - 1 > mheights[i - 1][j]) mheights[i - 1][j] = h - 1, pq.push({h - 1, {i - 1, j}});
    if (i < r - 1 && h - 1 > mheights[i + 1][j]) mheights[i + 1][j] = h - 1, pq.push({h - 1, {i + 1, j}});
    if (j > 0 && h - 1 > mheights[i][j - 1]) mheights[i][j - 1] = h - 1, pq.push({h - 1, {i, j - 1}});
    if (j < c - 1 && h - 1 > mheights[i][j + 1]) mheights[i][j + 1] = h - 1, pq.push({h - 1, {i, j + 1}});
  }
  
  cout << "Case #" << tc << ": " << t << '\n';
}

int main() {
  fast_io();
  
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) solve(i);
}
