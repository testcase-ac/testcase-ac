#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 30;
const int dx[6] = {0, 0, 0, 0, 1, -1}, dy[6] = {0, 0, 1, -1, 0, 0}, dl[6] = {1, -1, 0, 0, 0, 0};
const int INF = 0x3f3f3f3f;
char board[MAX][MAX][MAX];
int cdist[MAX][MAX][MAX];

int L, R, C;
void solve() {
  int sl, si, sj;
  for (int l = 0; l < L; l++) for (int i = 0; i < R; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < C; j++) {
      board[l][i][j] = s[j];
      if (s[j] == 'S') sl = l, si = i, sj = j;
    }
  }

  memset(cdist, INF, sizeof(cdist));

  queue<tuple<int, int, int, int>> q;
  q.push(make_tuple(sl, si, sj, 0));
  cdist[sl][si][sj] = 0;

  while (!q.empty()) {
    auto [l, i, j, c] = q.front(); q.pop();

    if (board[l][i][j] == 'E') {
      cout << "Escaped in " << c << " minute(s).\n";
      return;
    }

    for (int k = 0; k < 6; k++) {
      int nl = l + dl[k], ni = i + dy[k], nj = j + dx[k];
      if (nl < 0 || nl >= L || ni < 0 || ni >= R || nj < 0 || nj >= C) continue;
      if (board[nl][ni][nj] == '#') continue;
      if (cdist[nl][ni][nj] <= c + 1) continue;
      cdist[nl][ni][nj] = c + 1;
      q.push(make_tuple(nl, ni, nj, c + 1));
    }
  }

  cout << "Trapped!\n";
}

int main() {
  fast_io();

  while (cin >> L >> R >> C) {
    if (L == 0 && R == 0 && C == 0) break;
    solve();
  }
}
