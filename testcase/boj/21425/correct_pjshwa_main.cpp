#include <bits/stdc++.h>
#define pll pair<ll, ll>
#define pllpi pair<pll, int>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50;
char board[MAX + 1][MAX + 1][MAX + 1];
bool vis[MAX][MAX][MAX];

int main() {
  fast_io();

  int h, n, m;
  cin >> h >> n >> m;
  for (int i = 0; i < h; i++) for (int j = 0; j < n; j++) cin >> board[i][j];

  int sh, si, sj, eh, ei, ej;
  for (int k = 0; k < h; k++) for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[k][i][j] == '1') sh = k, si = i, sj = j;
    if (board[k][i][j] == '2') board[k][i][j] = '.', eh = k, ei = i, ej = j;
  }

  queue<tuple<int, int, int, int>> q;
  q.push(make_tuple(sh, si, sj, 0));
  vis[sh][si][sj] = true;

  while (!q.empty()) {
    auto [ch, i, j, cnt] = q.front();
    q.pop();

    if (ch == eh && i == ei && j == ej) return cout << cnt * 5 << '\n', 0;

    if (ch + 1 < h && !vis[ch + 1][i][j] && board[ch + 1][i][j] == '.') {
      vis[ch + 1][i][j] = true;
      q.push(make_tuple(ch + 1, i, j, cnt + 1));
    }
    if (i > 0 && !vis[ch][i - 1][j] && board[ch][i - 1][j] == '.') {
      vis[ch][i - 1][j] = true;
      q.push(make_tuple(ch, i - 1, j, cnt + 1));
    }
    if (j > 0 && !vis[ch][i][j - 1] && board[ch][i][j - 1] == '.') {
      vis[ch][i][j - 1] = true;
      q.push(make_tuple(ch, i, j - 1, cnt + 1));
    }
    if (i + 1 < n && !vis[ch][i + 1][j] && board[ch][i + 1][j] == '.') {
      vis[ch][i + 1][j] = true;
      q.push(make_tuple(ch, i + 1, j, cnt + 1));
    }
    if (j + 1 < m && !vis[ch][i][j + 1] && board[ch][i][j + 1] == '.') {
      vis[ch][i][j + 1] = true;
      q.push(make_tuple(ch, i, j + 1, cnt + 1));
    }
  }
}
