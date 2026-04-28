#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, INF = 0x3f3f3f3f;
int A[MAX], B[MAX], d[MAX][MAX];
int M, N;

int r(int i, int j) {
  if (j == N) return 0;
  if (i == M) return INF;
  if (d[i][j] != -1) return d[i][j];

  int ret = r(i + 1, j);
  ret = min(ret, r(i + 1, j + 1) + abs(A[i] - B[j]));
  return d[i][j] = ret;
}

void solve() {
  cin >> N >> M;
  if (N > M) {
    swap(N, M);
    for (int i = 0; i < M; i++) cin >> A[i];
    for (int i = 0; i < N; i++) cin >> B[i];
  }
  else {
    for (int i = 0; i < N; i++) cin >> B[i];
    for (int i = 0; i < M; i++) cin >> A[i];
  }
  sort(A, A + M);
  sort(B, B + N);

  memset(d, -1, sizeof(d));
  cout << r(0, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
