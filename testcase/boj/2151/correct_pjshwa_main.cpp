#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2500;
vector<int> graph[2 * MAX];
char board[51][51];
bool vis[2 * MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> board[i];

  int sv = -1, ev = -1;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    if (board[i][j] == '.' || board[i][j] == '*') continue;
    if (board[i][j] == '#') {
      if (sv == -1) sv = i * n + j;
      else ev = i * n + j;
    }

    for (int k = i + 1; k < n; k++) {
      if (board[k][j] == '!' || board[k][j] == '#') {
        int u = i * n + j, v = k * n + j;
        graph[u].push_back(v + MAX);
        graph[u + MAX].push_back(v);
        graph[v].push_back(u + MAX);
        graph[v + MAX].push_back(u);
      }
      else if (board[k][j] == '*') break;
    }

    for (int k = j + 1; k < n; k++) {
      if (board[i][k] == '!' || board[i][k] == '#') {
        int u = i * n + j, v = i * n + k;
        graph[u].push_back(v + MAX);
        graph[u + MAX].push_back(v);
        graph[v].push_back(u + MAX);
        graph[v + MAX].push_back(u);
      }
      else if (board[i][k] == '*') break;
    }
  }

  queue<pii> q;
  for (int v : {sv, sv + MAX}) {
    q.push({v, 0});
    vis[v] = true;
  }

  while (!q.empty()) {
    auto [cv, cc] = q.front();
    q.pop();

    if (cv == ev || cv == ev + MAX) {
      cout << cc - 1 << '\n';
      return;
    }

    for (int v : graph[cv]) {
      if (vis[v]) continue;
      vis[v] = true;
      q.push({v, cc + 1});
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
