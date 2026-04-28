#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using uii = unordered_map<int, int>;

const int MAX = 1e4, INF = 1e9 + 7;
int seq[MAX + 1], d[MAX + 1][13][13];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int dist(int x, int y) {
  return abs((x - 1) % 3 - (y - 1) % 3) + abs((x - 1) / 3 - (y - 1) / 3);
}

int main() {
  fast_io();

  int n, a, b;
  cin >> n >> a >> b;
  for (int i = 1; i <= n; i++) cin >> seq[i];

  for (int i = 0; i <= n; i++) for (int j = 0; j <= 12; j++) for (int k = 0; k <= 12; k++) d[i][j][k] = INF;

  d[0][1][3] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= 12; j++) for (int k = 1; k <= 12; k++) {
      d[i][seq[i]][k] = min(d[i][seq[i]][k], d[i - 1][j][k] + dist(j, seq[i]) + a);
    }
    for (int j = 1; j <= 12; j++) for (int k = 1; k <= 12; k++) {
      d[i][j][seq[i]] = min(d[i][j][seq[i]], d[i - 1][j][k] + dist(k, seq[i]) + b);
    }
  }

  int ans = INF;
  for (int j = 1; j <= 12; j++) for (int k = 1; k <= 12; k++) ans = min(ans, d[n][j][k]);
  cout << ans << '\n';
}
