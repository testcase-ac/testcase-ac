#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int A[MAX + 1][MAX + 1], d[MAX + 1][MAX + 1][40];
vector<int> factors;
int N;

int r(int i, int j, int k) {
  if (d[i][j][k] != -1) return d[i][j][k];

  bool ret = false;
  for (int nk = 0; nk < k; nk++) {
    if (factors[k] % factors[nk] == 0) ret |= !r(i, j, nk);
  }

  int lb = 1, ub = factors[k];
  for (int dx = lb; dx <= ub; dx++) {
    int nx = i + dx, ny = j;
    if (nx >= N || A[nx][ny]) break;
    ret |= !r(nx, ny, k);
  }
  for (int dy = lb; dy <= ub; dy++) {
    int nx = i, ny = j + dy;
    if (ny >= N || A[nx][ny]) break;
    ret |= !r(nx, ny, k);
  }

  return d[i][j][k] = ret;
}

void solve() {
  int K; cin >> N >> K;
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) cin >> A[i][j];

  // max factors size = 32 for K <= 1000
  for (int f = 1; f <= K; f++) {
    if (K % f) continue;
    factors.push_back(f);
  }

  memset(d, -1, sizeof(d));
  cout << r(0, 0, factors.size() - 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
