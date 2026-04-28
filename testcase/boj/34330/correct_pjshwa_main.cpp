#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
ll R[MAXN + 1], Xi[MAXN + 1], Yi[MAXN + 1], Xj[MAXN + 1], Yj[MAXN + 1];
int parent[MAXN + 1], V[MAXN + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[y] = x;
}

bool overlaps(int i, int j) {
  ll dx = Xi[i] - Xi[j], dy = Yi[i] - Yi[j];
  ll dist_sq = dx * dx + dy * dy;
  ll rad_sum = R[i] + R[j];
  return dist_sq <= rad_sum * rad_sum;
}

void solve() {
  int L, N, M; cin >> R[0] >> L >> N >> M;
  for (int i = 1; i <= N; ++i) cin >> Xi[i] >> Yi[i] >> R[i];
  for (int j = 1; j <= M; ++j) cin >> Xj[j] >> Yj[j];

  iota(parent, parent + N + 1, 0);
  for (int i = 1; i <= N; ++i) for (int j = i + 1; j <= N; ++j) {
    if (overlaps(i, j)) Union(i, j);
  }

  for (int i = 1; i <= N; ++i) {
    ll dx = Xi[i], dy = Yi[i];
    ll dist_sq = dx * dx + dy * dy;
    ll rad_diff = R[0] - R[i];
    if (R[i] >= R[0] || dist_sq >= rad_diff * rad_diff) Union(0, i);
  }

  for (int j = 1; j <= M; ++j) {
    for (int i = 1; i <= N; ++i) {
      if (Find(i) != Find(0)) continue;
      ll dx = Xi[i] - Xj[j], dy = Yi[i] - Yj[j];
      ll dist_sq = dx * dx + dy * dy;
      ll rad_sum = R[i] + L;
      if (dist_sq <= rad_sum * rad_sum) V[j] = 1;
    }
    ll dx = Xj[j], dy = Yj[j];
    ll dist_sq = dx * dx + dy * dy;
    ll rad_diff = R[0] - L;
    if (L >= R[0] || dist_sq >= rad_diff * rad_diff) V[j] = 1;
  }
  cout << accumulate(V + 1, V + M + 1, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
