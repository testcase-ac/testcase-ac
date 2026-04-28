#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1250;
char board[MAX + 1][MAX + 1];
bool vis[MAX][MAX];
int n;
int mi, mj;

void dfs(int i, int j) {
  vis[i][j] = true;
  mi = max(mi, i);
  mj = max(mj, j);
  if (i > 0 && !vis[i - 1][j]) dfs(i - 1, j);
  if (j > 0 && !vis[i][j - 1]) dfs(i, j - 1);
  if (i < n - 1 && !vis[i + 1][j]) dfs(i + 1, j);
  if (j < n - 1 && !vis[i][j + 1]) dfs(i, j + 1);
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) cin >> board[i];
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    if (board[i][j] == '.') vis[i][j] = 1;
  }

  vector<tuple<int, int, int, string>> ans;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    if (vis[i][j]) continue;

    // Always a corner position of fossil
    mi = mj = 0;
    dfs(i, j);

    int slen = mi - i + 1;
    int ci = (mi + i) / 2, cj = (mj + j) / 2;
    string t;

    if (board[i][j + 1] == '.') t = "UL";
    if (board[i][mj - 1] == '.') t = "UR";
    if (board[i + 1][j] == '.') t = "LU";
    if (board[i + 1][mj] == '.') t = "RU";
    if (board[mi - 1][j] == '.') t = "LD";
    if (board[mi - 1][mj] == '.') t = "RD";
    if (board[mi][j + 1] == '.') t = "DL";
    if (board[mi][mj - 1] == '.') t = "DR";

    ans.push_back(make_tuple(ci, cj, slen, t));
  }
  sort(ans.begin(), ans.end());

  cout << ans.size() << '\n';
  for (auto &e : ans) {
    auto [ci, cj, slen, t] = e;
    cout << ci + 1 << " " << cj + 1 << " " << slen << " " << t << '\n';
  }
}
