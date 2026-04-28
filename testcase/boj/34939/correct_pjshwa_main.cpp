#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int A[MAXN + 1], B[MAXN + 1], N, L = 0, maxL, x, flag;

void bmove() {
  int nx = x + A[x];
  if (A[x]-- > 0 && nx <= N) x = nx, ++L;
  else flag = 0;
}

void dfs_search(int i) {
  if (i == N) {
    copy(B + 1, B + N + 1, A + 1);

    L = 0;
    for (int t = 1; t <= N; ++t) {
      x = flag = 1;
      while (flag) bmove();
    }
    maxL = max(maxL, L);

  } else {
    for (int v = 0; v < N; ++v) {
      B[i] = v;
      dfs_search(i + 1);
    }
  }
}

void dfs_print(int i) {
  if (i == N) {
    copy(B + 1, B + N + 1, A + 1);

    L = 0;
    for (int t = 1; t <= N; ++t) {
      x = flag = 1;
      while (flag) bmove();
    }
    if (L == maxL) {
      cout << "A = ";
      for (int j = 1; j <= N; ++j) cout << B[j] << ' ';
      cout << ", L = " << L << '\n';
    }

  } else {
    for (int v = 0; v < N; ++v) {
      B[i] = v;
      dfs_print(i + 1);
    }
  }
}

void solve() {
  cin >> N;

  // for (int t = 1; t <= N; ++t) cin >> A[t];
  A[1] = N - 1; int t = 1, v = 1;
  while (t <= N) {
    int j = v++;
    for (int k = 0; k < j; ++k) {
      A[++t] = j;
      if (t > N) break;
    }
  }

  // cout << "A = ";
  for (int i = 1; i <= N; ++i) cout << A[i] << ' ';
  cout << '\n';
  return;

  for (int t = 1; t <= N; ++t) {
    x = flag = 1; ++L;
    while (flag) bmove();
    // cout << "A = ";
    // for (int i = 1; i <= N; ++i) cout << A[i] << ' ';
    // cout << ", L = " << L << '\n';
  }
  // cout << "L = " << L << '\n';
  return;

  dfs_search(1);
  dfs_print(1);
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
