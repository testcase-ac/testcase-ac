#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100, INF = 0x3f3f3f3f;
const int dx[4] = {-1, -1, 1, 1}, dy[4] = {-1, 1, -1, 1};
int A[MAX][MAX], cdist[MAX][MAX];
int dst[11][11];

int dist(pii a, pii b) {
  return max(abs(a.first - b.first), abs(a.second - b.second));
}

void solve() {
  int N;
  cin >> N;

  int si, sj;
  vector<pii> enemies;
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
    cin >> A[i][j];
    if (A[i][j] == 1) enemies.push_back({i, j});
    if (A[i][j] == 2) si = i, sj = j;
  }
  if (enemies.empty()) return cout << "Undertaker\n0\n", void();

  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
    if (A[i][j] != 1) continue;
    if (((si + sj) & 1) == ((i + j) & 1)) continue;
    return cout << "Shorei\n", void();
  }

  int z = enemies.size();
  for (int i = 0; i <= z; i++) for (int j = 0; j <= z; j++) {
    int xi, yi, xj, yj;
    if (i == z) xi = si, yi = sj;
    else tie(xi, yi) = enemies[i];
    if (j == z) xj = si, yj = sj;
    else tie(xj, yj) = enemies[j];

    dst[i][j] = dist({xi, yi}, {xj, yj});
  }

  int p[z];
  for (int i = 0; i < z; i++) p[i] = i;

  int ans = INF;
  do {
    int cur = dst[z][p[0]];
    for (int i = 0; i < z - 1; i++) cur += dst[p[i]][p[i + 1]];
    ans = min(ans, cur);
  } while (next_permutation(p, p + z));

  cout << "Undertaker\n" << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
