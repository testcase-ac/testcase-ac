#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 20, INF = 0x3f3f3f3f;
vector<pii> deps[MAXN];
int dp[1 << MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) {
    int pi; cin >> pi;
    while (pi--) {
      int l, k, x, dep = 0; cin >> l >> k;
      while (k--) cin >> x, dep |= 1 << x;
      deps[i].emplace_back(l, dep);
    }
  }

  memset(dp, 0x3f, sizeof(dp));
  vector<int> sets;
  for (int s = 0; s < (1 << N); ++s) sets.push_back(s);
  sort(sets.begin(), sets.end(), [](int a, int b) {
    return __builtin_popcount(a) < __builtin_popcount(b);
  });

  dp[0] = 0;
  for (int s : sets) {
    for (int i = 0; i < N; ++i) {
      if (s & (1 << i)) continue;

      // see if we can prove i with s
      int mlen = INF;
      for (auto& [l, dep] : deps[i]) {
        if ((s & dep) == dep) mlen = min(mlen, l);
      }
      dp[s | (1 << i)] = min(dp[s | (1 << i)], dp[s] + mlen);
    }
  }

  int ans = INF;
  for (int s = 0; s < (1 << N); ++s) {
    if (s & 1) ans = min(ans, dp[s]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
