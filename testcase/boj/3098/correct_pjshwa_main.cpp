#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50, INF = 0x3f3f3f3f;
vector<int> graph[MAX + 1];
int cdist[MAX + 1][MAX + 1], T[MAX + 1];

void solve() {
  int N, M;
  cin >> N >> M;
  while (M--) {
    int A, B;
    cin >> A >> B;
    graph[A].push_back(B);
    graph[B].push_back(A);
  }

  for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) cdist[i][j] = INF;

  queue<pii> q;
  for (int i = 1; i <= N; i++) {
    cdist[i][i] = 0;
    q.push({i, 0});

    while (!q.empty()) {
      auto [v, c] = q.front(); q.pop();

      for (int u : graph[v]) {
        if (cdist[i][u] > c + 1) {
          cdist[i][u] = c + 1;
          q.push({u, c + 1});
        }
      }
    }
  }

  int ans = 0;
  for (int i = 1; i <= N; i++) for (int j = i + 1; j <= N; j++) {
    int val;
    if (cdist[i][j] <= 1) val = 0;
    else if (cdist[i][j] <= 2) val = 1;
    else if (cdist[i][j] <= 4) val = 2;
    else if (cdist[i][j] <= 8) val = 3;
    else if (cdist[i][j] <= 16) val = 4;
    else if (cdist[i][j] <= 32) val = 5;
    else if (cdist[i][j] <= 64) val = 6;

    ans = max(ans, val);
    T[val]++;
  }

  cout << ans << '\n';
  for (int i = 1; i <= ans; i++) cout << T[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
