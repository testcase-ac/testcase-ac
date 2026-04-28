#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 200, INF = 1e9 + 7;
int cost[MAX][MAX];

int main() {
  fast_io();

  int n;
  cin >> n;
  vector<tuple<int, int, int>> v(n);
  for (int i = 0; i < n; i++) {
    int x, y, p;
    cin >> x >> y >> p;
    v[i] = make_tuple(x, y, p);
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j) cost[i][j] = INF;
    }
  }

  for (int i = 0; i < n; i++) {
    auto [x1, y1, p] = v[i];
    for (int j = 0; j < n; j++) {
      auto [x2, y2, _] = v[j];
      int dist = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
      if (dist <= p * p) cost[i][j] = 1;
    }
  }

  // Floyd-Warshall
  for (int k = 0; k < n; k++) for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    int cnt = 0;
    for (int j = 0; j < n; j++) if (cost[i][j] != INF) cnt++;
    ans = max(ans, cnt);
  }
  cout << ans << endl;
}
