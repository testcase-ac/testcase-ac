#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

map<string, int> fi;
int fcount;
int fidx(string f) {
  auto found = fi.find(f);
  if (fi.end() == found) {
    fi.insert({f, fcount});
    return fcount++;
  }
  else return found->second;
}

const int MAXN = 12, MAXS = 18;
char board[MAXN + 1][MAXN + 1];
int L[MAXN][MAXN], Exi[MAXN][MAXN], Req[MAXN][MAXN], Win[MAXN][MAXN], N;
int vis[MAXN][MAXN];
vector<tuple<int, int, int>> adj[MAXN][MAXN];
int ok = 0;

void dfs(int i, int j, int l, int c, int s) {
  // cout << "dfs(" << i << ", " << j << ", " << l << ", " << c << ", " << s << ")\n";
  vis[i][j] = 1;
  if (i == 2 * N && j == 2 * N) {
    ok = 1;
    return;
  }
  if (s == MAXS) {
    vis[i][j] = 0;
    return;
  }

  for (auto& [ni, nj, nl] : adj[i][j]) {
    if (vis[ni][nj]) continue;
    if (nl > l) continue;

    // Boss is here
    if (ni % 2 == 1 && nj % 2 == 1) {
      int req = Req[ni / 2][nj / 2];
      if (!Exi[ni / 2][nj / 2]) dfs(ni, nj, l, c, s + 1);
      else if ((req & c) == req) {
        int win = Win[ni / 2][nj / 2];
        dfs(ni, nj, l + 1, c | win, s + 1);
      }
    } else {
      dfs(ni, nj, l, c, s + 1);
    }
  }
  vis[i][j] = 0;
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; ++i) cin >> board[i];
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> L[i][j];
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    string o, req, win; cin >> o >> req >> win;
    Exi[i][j] = o == "1";
    if (req != "0") Req[i][j] = 1 << fidx(req);
    if (win != "0") Win[i][j] = 1 << fidx(win);
  }

  // construct graph
  for (int i = 0; i <= 2 * N; i += 2) {
    for (int j = 1; j <= 2 * N; ++j) {
      int l = L[i / 2][(j - 1) / 2];
      if (i) l = max(l, L[i / 2 - 1][(j - 1) / 2]);

      adj[i][j].emplace_back(i, j - 1, l);
      adj[i][j - 1].emplace_back(i, j, l);
    }
  }
  for (int i = 1; i <= 2 * N; i += 2) {
    for (int j = 1; j <= 2 * N; ++j) {
      int l = L[i / 2][(j - 1) / 2];
      char c = board[i / 2][(j - 1) / 2];
      if (c != 'A' && c != 'B') continue;

      adj[i][j].emplace_back(i, j - 1, l);
      adj[i][j - 1].emplace_back(i, j, l);
    }
  }
  for (int j = 0; j <= 2 * N; j += 2) {
    for (int i = 1; i <= 2 * N; ++i) {
      int l = L[(i - 1) / 2][j / 2];
      if (j) l = max(l, L[(i - 1) / 2][j / 2 - 1]);

      adj[i][j].emplace_back(i - 1, j, l);
      adj[i - 1][j].emplace_back(i, j, l);
    }
  }
  for (int j = 1; j <= 2 * N; j += 2) {
    for (int i = 1; i <= 2 * N; ++i) {
      int l = L[(i - 1) / 2][j / 2];
      char c = board[(i - 1) / 2][j / 2];
      if (c != 'A' && c != 'C') continue;

      adj[i][j].emplace_back(i - 1, j, l);
      adj[i - 1][j].emplace_back(i, j, l);
    }
  }
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    char c = board[i][j];
    if (c != 'D') continue;

    int ci = 2 * i + 1, cj = 2 * j + 1;
    for (int di : {1, -1}) for (int dj : {1, -1}) {
      int ni = ci + di, nj = cj + dj;
      adj[ci][cj].emplace_back(ni, nj, L[i][j]);
      adj[ni][nj].emplace_back(ci, cj, L[i][j]);
    }
  }

  int c, C = 0; cin >> c;
  while (c--) {
    string win; cin >> win;
    C |= (1 << fidx(win));
  }

  dfs(0, 0, 1, C, 0);
  if (ok) cout << "Dreams Come True\n";
  else cout << "-1\n";

  // cout << "adj = ";
  // for (int i = 0; i <= 2 * N; ++i) {
  //   for (int j = 0; j <= 2 * N; ++j) {
  //     cout << "(" << i << ", " << j << ") = ";
  //     for (auto [ni, nj, l] : adj[i][j]) cout << "(" << ni << ", " << nj << ", " << l << ") ";
  //     cout << '\n';
  //   }
  // }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
