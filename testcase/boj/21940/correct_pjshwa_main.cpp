#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 200, INF = 1e9 + 7;
int cost[MAX + 1][MAX + 1];

void solve() {
  int N, M;
  cin >> N >> M;
  for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) {
    if (i != j) cost[i][j] = INF;
  }
  while (M--) {
    int Ai, Bi, Ti;
    cin >> Ai >> Bi >> Ti;
    cost[Ai][Bi] = Ti;
  }
  int K;
  cin >> K;
  vector<int> F(K);
  for (int i = 0; i < K; i++) cin >> F[i];

  // Floyd-Warshall
  for (int k = 1; k <= N; k++) for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) {
    cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
  }

  int mcost = INF;
  for (int k = 1; k <= N; k++) {
    int cur = 0;
    for (int i = 0; i < K; i++) cur = max(cur, cost[F[i]][k] + cost[k][F[i]]);
    mcost = min(mcost, cur);
  }

  for (int k = 1; k <= N; k++) {
    int cur = 0;
    for (int i = 0; i < K; i++) cur = max(cur, cost[F[i]][k] + cost[k][F[i]]);
    if (cur == mcost) cout << k << ' ';
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
