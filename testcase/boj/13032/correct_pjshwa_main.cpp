#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int A[MAXN], D[MAXN], dp[MAXN];

int rec(int i) {
  if (i <= 0) return 0;
  if (dp[i] != -1) return dp[i];

  int l = 0, r = i;
  while (l < r) {
    int m = (l + r) / 2;
    if (A[m] >= A[i] - D[i]) r = m;
    else l = m + 1;
  }
  return dp[i] = rec(l - 1) + i - l;
}

void solve() {
  int N; cin >> N;
  vector<pii> U;
  for (int i = 0; i < N; ++i) {
    int a, d; cin >> a >> d;
    U.emplace_back(a, d);
  }
  sort(U.begin(), U.end());
  for (int i = 0; i < N; ++i) {
    A[i] = U[i].first;
    D[i] = U[i].second;
  }

  memset(dp, -1, sizeof(dp)); int ans = N;
  for (int i = 0; i < N; ++i) ans = min(ans, rec(i) + N - i - 1);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
