#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int board[8][8], nboard[8][8];
int rs[8], cs[8], ss[8][8], nrs[8], ncs[8];
char ans[8][8];
int main() {
  fast_io();

  int m, nss;
  cin >> m >> nss;
  vector<pii> positions;

  for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) cin >> board[i][j];
  for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) rs[i] += board[i][j];
  for (int j = 0; j < 8; j++) for (int i = 0; i < 8; i++) cs[j] += board[i][j];
  for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) {
    ss[i][j] = rs[i] + cs[j] - board[i][j] - 15 * m;

    // abs(ss) is even, if (i, j) doesn't contain sprayer
    if (abs(ss[i][j]) & 1) positions.push_back({i, j});
  }

  for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) nboard[i][j] = m;

  for (auto [ci, cj] : positions) {
    for (int i = 0; i < 8; i++) nboard[i][cj]++;
    for (int j = 0; j < 8; j++) nboard[ci][j]++;
    nboard[ci][cj]--;
  }
  for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) nrs[i] += nboard[i][j];
  for (int j = 0; j < 8; j++) for (int i = 0; i < 8; i++) ncs[j] += nboard[i][j];

  for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) ans[i][j] = '.';
  for (auto [ci, cj] : positions) {
    nss = nrs[ci] + ncs[cj] - nboard[ci][cj] - 15 * m;
    if (abs(ss[ci][cj] - nss) % 4) ans[ci][cj] = '-';
    else ans[ci][cj] = '+';
  }

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) cout << ans[i][j] << ' ';
    cout << '\n';
  }
}
