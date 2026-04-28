#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50, INF = 1e9 + 7;
char board[MAX + 1][MAX + 1];
queue<pii> cpos[26];
vector<char> ans;

void move(pii s, pii e) {
  auto [sx, sy] = s;
  auto [ex, ey] = e;
  for (int i = sx; i < ex; i++) ans.push_back('D');
  for (int i = ex; i < sx; i++) ans.push_back('U');
  for (int i = sy; i < ey; i++) ans.push_back('R');
  for (int i = ey; i < sy; i++) ans.push_back('L');
}

void pickup() {
  ans.push_back('P');
}

void solve() {
  int N, M, T; string S;
  cin >> N >> M >> T;
  for (int i = 0; i < N; i++) cin >> board[i];
  cin >> S;

  map<int, int> ts, tb;
  for (char& c : S) ts[c - 'a']++;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    int ci = board[i][j] - 'a';
    tb[ci]++;
    cpos[ci].push({i, j});
  }

  int C = INF;
  for (auto& [k, v] : ts) C = min(C, tb[k] / v);

  pii last = {0, 0};
  for (int it = 0; it < C; it++) {
    for (char& c : S) {
      int ci = c - 'a';
      auto [nx, ny] = cpos[ci].front();
      cpos[ci].pop();

      move(last, {nx, ny});
      pickup();
      last = {nx, ny};
    }
  }
  move(last, {N - 1, M - 1});

  cout << C << ' ' << ans.size() << '\n';
  for (char& c : ans) cout << c;
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
