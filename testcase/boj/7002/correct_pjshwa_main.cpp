#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
char board[MAXN + 1][MAXN + 1];
int DL[MAXN + 1][MAXN + 1], DR[MAXN + 1][MAXN + 1];
int P[MAXN + 1][MAXN + 1];

void solve() {
  cout << "Maximum damage = ";

  int N, M, T, R; cin >> N >> M >> T >> R;
  for (int i = 0; i < N; ++i) cin >> board[i];

  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    DL[i][j] = DR[i][j] = 0;
  }
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (board[i][j] == 'O') DL[i][j] = DR[i][j] = 1;
    if (i > 0 && j < M - 1) DL[i][j] += DL[i - 1][j + 1];
    if (i > 0 && j > 0) DR[i][j] += DR[i - 1][j - 1];
  }

  int cnt = 0;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (board[i][j] == 'O' && i + j <= R) ++cnt;
  }

  auto dl_get = [&](int from_i, int from_j, int to_i, int to_j) {
    int to_dif = max({0, to_i - (N - 1), -to_j});
    to_i -= to_dif; to_j += to_dif;
    if (to_i < 0 || to_j >= M) return 0;

    int from_dif = max({0, -from_i, from_j - (M - 1)});
    from_i += from_dif; from_j -= from_dif;
    if (from_i >= N || from_j < 0) return 0;

    if (from_i > to_i || from_j < to_j) return 0;

    int ret = DL[to_i][to_j];
    if (from_i > 0 && from_j < M - 1) ret -= DL[from_i - 1][from_j + 1];
    return ret;
  };

  auto dr_get = [&](int from_i, int from_j, int to_i, int to_j) {
    int to_dif = max({0, to_i - (N - 1), to_j - (M - 1)});
    to_i -= to_dif; to_j -= to_dif;
    if (to_i < 0 || to_j < 0) return 0;

    int from_dif = max({0, -from_i, -from_j});
    from_i += from_dif; from_j += from_dif;
    if (from_i >= N || from_j >= M) return 0;

    if (from_i > to_i || from_j > to_j) return 0;

    int ret = DR[to_i][to_j];
    if (from_i > 0 && from_j > 0) ret -= DR[from_i - 1][from_j - 1];
    return ret;
  };

  for (int i = 0; i < N; ++i) {
    P[i][0] = cnt;
    for (int j = 1; j < M; ++j) {
      int pj = j - 1;

      int dl_sub = dl_get(i - R, pj, i, pj - R);
      int dr_sub = dr_get(i + 1, pj - R + 1, i + R, pj);
      int dl_add = dl_get(i, j + R, i + R, j);
      int dr_add = dr_get(i - R, j, i - 1, j + R - 1);

      cnt += dl_add + dr_add - dl_sub - dr_sub;
      P[i][j] = cnt;
    }

    cnt = P[i][0];
    int dl_sub = dl_get(i - R, 0, i, -R);
    int dr_sub = dr_get(i - R + 1, 1, i, R);
    int dl_add = dl_get(i + 1, R, i + R + 1, 0);
    int dr_add = dr_get(i + 1, -R, i + R, -1);
    cnt += dl_add + dr_add - dl_sub - dr_sub;
  }

  priority_queue<int> pq;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (board[i][j] == '*') pq.push(P[i][j]);
  }

  ll ans = 0;
  while (T-- && !pq.empty()) {
    ans += pq.top();
    pq.pop();
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
