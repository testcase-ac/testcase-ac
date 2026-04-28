#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, MAXC = 16, INF = 0x3f3f3f3f;
int W[MAXC + 1][MAXC + 1], A[MAX + 1], B[MAX + 1];

// Closest index from index i that has personality j
int AL[MAX + 1][MAXC + 1], BL[MAX + 1][MAXC + 1];
int N, M, C;

ll d[MAX + 10][MAX + 10];

ll r(int i, int j) {
  if (d[i][j] != -1) return d[i][j];
  if (i == N + 1 || j == M + 1) return d[i][j] = 0;

  ll ret = 0;
  if (i <= N) ret = max(ret, r(i + 1, j));
  if (j <= M) ret = max(ret, r(i, j + 1));

  // Match current i with personality c
  for (int c = 1; c <= C; c++) {
    int nj = BL[j][c];
    if (nj == -1) continue;

    ll gain = W[A[i]][c];
    ret = max(ret, r(i + 1, nj + 1) + gain);
  }

  // Match current j with personality c
  for (int c = 1; c <= C; c++) {
    int ni = AL[i][c];
    if (ni == -1) continue;

    ll gain = W[B[j]][c];
    ret = max(ret, r(ni + 1, j + 1) + gain);
  }

  return d[i][j] = ret;
}

void solve() {
  cin >> N >> M >> C;
  for (int i = 1; i <= C; i++) for (int j = 1; j <= C; j++) cin >> W[i][j];

  for (int i = 1; i <= N; i++) cin >> A[i];
  for (int i = 1; i <= M; i++) cin >> B[i];

  for (int i = 1; i <= N; i++) {
    fill(AL[i], AL[i] + C + 1, -1);
    for (int j = N; j >= i; j--) {
      AL[i][A[j]] = j;
    }
  }
  for (int i = 1; i <= M; i++) {
    fill(BL[i], BL[i] + C + 1, -1);
    for (int j = M; j >= i; j--) {
      BL[i][B[j]] = j;
    }
  }

  memset(d, -1, sizeof(d));
  cout << r(1, 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
