#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
ll A[MAXN], C, ans;

void dfs(int i, ll sum) {
  if (i < 0) {
    ans = max(ans, sum);
    return;
  }

  if (sum + A[i] > C) dfs(i - 1, sum);
  else if (i > 0 && sum + A[i - 1] + A[i] > C) {
    dfs(i - 2, sum + A[i - 1]);
    dfs(i - 2, sum + A[i]);
  }
  else dfs(i - 1, sum + A[i]);
}

void solve() {
  int N; cin >> N >> C;
  for (int i = 0; i < N; ++i) cin >> A[i];

  dfs(N - 1, 0);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
