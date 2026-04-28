#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 1e6, INF = 0x3f3f3f3f;
int dp[MAXV + 1], Qv[MAXV + 1];

void solve() {
  int N, Q; cin >> N >> Q;

  vector<pii> A, B;
  for (int i = 0; i < N; ++i) {
    int p, l; cin >> p >> l;
    A.emplace_back(p, l);
  }
  sort(A.begin(), A.end(), [&](const pii& a, const pii& b) {
    return a.second < b.second;
  });
  for (int i = 0; i < Q; ++i) {
    int p, l; cin >> p >> l;
    B.emplace_back(p, l);
  }

  fill(dp, dp + MAXV + 1, -INF); dp[0] = 0;
  for (int i = 0; i < N; ++i) {
    auto& [p, l] = A[i];
    for (int v = MAXV; v >= p; --v) {
      dp[v] = max(dp[v], dp[v - p] + l);
    }
    for (int j = 0; j < Q; ++j) {
      auto& [qp, ql] = B[j];
      Qv[j] |= (dp[qp] >= ql && l <= ql);
    }
  }

  for (int i = 0; i < Q; ++i) cout << (Qv[i] ? "YES" : "NO") << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
