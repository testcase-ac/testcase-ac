#include <bits/stdc++.h>
#define pii pair<int, int>
#define pipii pair<int, pii>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 125, INF = 1e9 + 7;
int board[MAX][MAX], cdist[MAX][MAX];
int n, tc;

void dijk(pii s) {
  cdist[s.first][s.second] = 0;
  priority_queue<pipii, vector<pipii>, greater<pipii>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto [wi, u] = pq.top();
    auto [ui, uj] = u;
    pq.pop();

    if (wi > cdist[ui][uj]) continue;

    if (ui > 0 && cdist[ui - 1][uj] > wi + board[ui - 1][uj]) {
      cdist[ui - 1][uj] = wi + board[ui - 1][uj];
      pq.push({cdist[ui - 1][uj], {ui - 1, uj}});
    }
    if (ui < n - 1 && cdist[ui + 1][uj] > wi + board[ui + 1][uj]) {
      cdist[ui + 1][uj] = wi + board[ui + 1][uj];
      pq.push({cdist[ui + 1][uj], {ui + 1, uj}});
    }
    if (uj > 0 && cdist[ui][uj - 1] > wi + board[ui][uj - 1]) {
      cdist[ui][uj - 1] = wi + board[ui][uj - 1];
      pq.push({cdist[ui][uj - 1], {ui, uj - 1}});
    }
    if (uj < n - 1 && cdist[ui][uj + 1] > wi + board[ui][uj + 1]) {
      cdist[ui][uj + 1] = wi + board[ui][uj + 1];
      pq.push({cdist[ui][uj + 1], {ui, uj + 1}});
    }
  }
}

void solve() {
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> board[i][j];
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cdist[i][j] = INF;
  dijk({0, 0});
  cout << "Problem " << ++tc << ": " << board[0][0] + cdist[n - 1][n - 1] << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> n;
    if (n == 0) break;

    solve();
  }
}
