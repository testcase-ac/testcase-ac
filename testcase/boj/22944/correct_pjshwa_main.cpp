#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500, INF = 1e9 + 7;
char board[MAX + 1][MAX + 1];
int si, sj, ei, ej, d, ans = INF;
bool uvis[10];
vector<pii> us;

int manhattan_dist(int ai, int aj, int bi, int bj) {
  return abs(ai - bi) + abs(aj - bj);
}

void dfs(int ci, int cj, int ch, int ubonus, int tdist) {
  int edist = manhattan_dist(ci, cj, ei, ej);
  if (ch + ubonus >= edist) {
    ans = min(ans, tdist + edist);
    return;
  }

  for (int i = 0; i < us.size(); i++) {
    if (uvis[i]) continue;
    auto [ui, uj] = us[i];
    int udist = manhattan_dist(ci, cj, ui, uj);

    if (ch + ubonus >= udist) {
      uvis[i] = true;
      dfs(ui, uj, ch - max(0, udist - ubonus), d, tdist + udist);
      uvis[i] = false;
    }
  }
}

void solve() {
  int n, h;
  cin >> n >> h >> d;
  for (int i = 0; i < n; i++) cin >> board[i];

  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    if (board[i][j] == 'S') si = i, sj = j;
    if (board[i][j] == 'E') ei = i, ej = j;
    if (board[i][j] == 'U') us.push_back({i, j});
  }

  dfs(si, sj, h, 0, 0);

  if (ans == INF) cout << -1 << '\n';
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
