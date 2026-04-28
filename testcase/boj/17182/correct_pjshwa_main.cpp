#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int cost[10][10];
const int INF = 1e9 + 7;

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;

  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> cost[i][j];

  // Floyd-warshall
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) cost[i][j] = min(cost[i][k] + cost[k][j], cost[i][j]);
    }
  }

  int p[n];
  for (int i = 0; i < n; i++) p[i] = i;

  int ans = INF;
  do {
    if (p[0] != k) continue;

    int cur = 0;
    for (int i = 0; i < n - 1; i++) cur += cost[p[i]][p[i + 1]];
    ans = min(ans, cur);

  } while (next_permutation(p, p + n));
  cout << ans << '\n';
}
