#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int ones_in_base2(int n) {
  int ret = 0;
  while (n) {
    ret += n % 2;
    n /= 2;
  }
  return ret;
}

int ones_in_base3(int n) {
  int ret = 0;
  while (n) {
    ret += (n % 3) == 1;
    n /= 3;
  }
  return ret;
}

const int MAXN = 20;
int A[MAXN];
ll dp[MAXN][1 << MAXN];
vector<int> adj[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];

  for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) {
    if (ones_in_base2(A[i]) == ones_in_base2(A[j])) {
      adj[i].push_back(j);
      adj[j].push_back(i);
    }
    else if (ones_in_base3(A[i]) == ones_in_base3(A[j])) {
      adj[i].push_back(j);
      adj[j].push_back(i);
    }
  }

  for (int i = 0; i < N; ++i) dp[i][1 << i] = 1;

  for (int s = 1; s < (1 << N); ++s) {

    for (int u = 0; u < N; ++u) {
      if (!(s & (1 << u))) continue;
      for (int v : adj[u]) {
        if (!(s & (1 << v))) continue;
        dp[u][s] += dp[v][s ^ (1 << u)];
      }
    }

  }

  ll ans = 0;
  for (int i = 0; i < N; ++i) ans += dp[i][(1 << N) - 1];
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
