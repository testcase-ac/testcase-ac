#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int N, M, c1, c2; cin >> N >> M >> c1 >> c2;
  vector<int> A(N), B(M);
  for (int i = 0; i < N; ++i) cin >> A[i];
  for (int i = 0; i < M; ++i) cin >> B[i];
  sort(A.begin(), A.end());
  sort(B.begin(), B.end());

  int bi = 0, ans = INF;
  auto update_ans = [&](int ai, int bi) {
    if (bi < 0 || bi >= M) return;
    ans = min(ans, abs(A[ai] - B[bi]));
  };

  for (int ai = 0; ai < N; ++ai) {
    while (bi < M && B[bi] <= A[ai]) ++bi;
    update_ans(ai, bi - 1);
    update_ans(ai, bi);
  }

  ll cnt = 0;
  for (int ai = 0; ai < N; ++ai) {
    cnt += upper_bound(B.begin(), B.end(), A[ai] + ans) - lower_bound(B.begin(), B.end(), A[ai] + ans);
    cnt += upper_bound(B.begin(), B.end(), A[ai] - ans) - lower_bound(B.begin(), B.end(), A[ai] - ans);
  }
  if (ans == 0) cnt /= 2;

  cout << ans + abs(c1 - c2) << ' ' << cnt << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
