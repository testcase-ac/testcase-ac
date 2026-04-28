#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 50;
int B[MAXN + 1][MAXN + 1], OB[MAXN + 1][MAXN + 1], N, M;

void copy() {
  for (int i = 1; i <= N; ++i) for (int j = 1; j <= M; ++j) B[i][j] = OB[i][j];
}

int arr_val() {
  int ret = INT_MAX;
  for (int i = 1; i <= N; ++i) {
    int cur = 0;
    for (int j = 1; j <= M; ++j) cur += B[i][j];
    ret = min(ret, cur);
  }
  return ret;
}

void rotate(int r, int c, int s) {
  vector<int> pre;
  for (int d = 1; d <= s; ++d) {
    for (int j = c - d; j < c + d; ++j) pre.push_back(B[r - d][j]);
    for (int i = r - d; i < r + d; ++i) pre.push_back(B[i][c + d]);
    for (int j = c + d; j > c - d; --j) pre.push_back(B[r + d][j]);
    for (int i = r + d; i > r - d; --i) pre.push_back(B[i][c - d]);

    int b = pre.back(), it = 0; pre.pop_back();
    pre.insert(pre.begin(), b);

    for (int j = c - d; j < c + d; ++j) B[r - d][j] = pre[it++];
    for (int i = r - d; i < r + d; ++i) B[i][c + d] = pre[it++];
    for (int j = c + d; j > c - d; --j) B[r + d][j] = pre[it++];
    for (int i = r + d; i > r - d; --i) B[i][c - d] = pre[it++];

    pre.clear();
  }
}

void solve() {
  int K; cin >> N >> M >> K;
  for (int i = 1; i <= N; ++i) for (int j = 1; j <= M; ++j) cin >> OB[i][j];

  vector<tuple<int, int, int>> Qs;
  for (int i = 0; i < K; ++i) {
    int r, c, s; cin >> r >> c >> s;
    Qs.emplace_back(r, c, s);
  }

  int P[K], ans = INT_MAX; iota(P, P + K, 0);
  do {
    copy();
    for (int i = 0; i < K; ++i) {
      auto [r, c, s] = Qs[P[i]];
      rotate(r, c, s);
    }
    ans = min(ans, arr_val());
  } while (next_permutation(P, P + K));

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
