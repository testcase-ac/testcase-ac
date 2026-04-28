#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500, INF = 1e9 + 7;
pii cost[MAX + 1];
int d[MAX + 1][MAX + 1];
int n;

int min_cost(int l, int r) {
  if (l == r) return 0;
  if (d[l][r] != -1) return d[l][r];

  int ans = INF;
  for (int i = l; i < r; i++) {
    int m = cost[l].first * cost[r].second;
    ans = min(ans, min_cost(l, i) + min_cost(i + 1, r) + m * cost[i].second);
  }
  return d[l][r] = ans;
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 1; i <= n; i++) cin >> cost[i].first >> cost[i].second;
  memset(d, -1, sizeof(d));
  cout << min_cost(1, n) << '\n';
}
