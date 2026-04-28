#include <bits/stdc++.h>
typedef long long ll;
#define pll pair<ll, ll>
using namespace std;

const int MAX = 3e4;
const ll INF = 1e14;
ll cdist[MAX + 1];
vector<pll> graph[MAX + 1];

void dijk(int s) {
  cdist[s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto[wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (auto &p : graph[ui]) {
      auto[vi, di] = p;
      if (cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, t, bias = 1e4;
  cin >> n >> t;
  int board[n][n];
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> board[i][j];

  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    if (i - 1 >= 0) {
      int cur = i * n + j, nxt = (i - 1) * n + j;
      graph[cur].push_back({nxt + bias, t});
      graph[cur + bias].push_back({nxt + 2 * bias, t});
      graph[cur + 2 * bias].push_back({nxt, t + board[i - 1][j]});
    }
    if (i + 1 < n) {
      int cur = i * n + j, nxt = (i + 1) * n + j;
      graph[cur].push_back({nxt + bias, t});
      graph[cur + bias].push_back({nxt + 2 * bias, t});
      graph[cur + 2 * bias].push_back({nxt, t + board[i + 1][j]});
    }
    if (j - 1 >= 0) {
      int cur = i * n + j, nxt = i * n + j - 1;
      graph[cur].push_back({nxt + bias, t});
      graph[cur + bias].push_back({nxt + 2 * bias, t});
      graph[cur + 2 * bias].push_back({nxt, t + board[i][j - 1]});
    }
    if (j + 1 < n) {
      int cur = i * n + j, nxt = i * n + j + 1;
      graph[cur].push_back({nxt + bias, t});
      graph[cur + bias].push_back({nxt + 2 * bias, t});
      graph[cur + 2 * bias].push_back({nxt, t + board[i][j + 1]});
    }
  }

  fill(cdist, cdist + MAX + 1, INF);
  dijk(0);

  int dst = n * n - 1;
  cout << min({cdist[dst], cdist[dst + bias], cdist[dst + 2 * bias]}) << '\n';
}
