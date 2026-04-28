#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void compress(vector<int>& v) {
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
}

const int MAXN = 2000;
int dp[MAXN + 1];

int rec(int n) {
  if (dp[n] != -1) return dp[n];
  if (n == 1) return dp[n] = 0;

  vector<int> Gs;
  for (int k = 1; k < n; ++k) {
    int s = n / k, r = rec(n % k);
    if (s & 1) r ^= rec(k);
    Gs.push_back(r);
  }
  compress(Gs);

  // calculate mex of Gs
  int mex = 0;
  for (int g : Gs) {
    if (g == mex) ++mex;
  }
  return dp[n] = mex;
}

void solve() {
  int N, ans = 0; cin >> N;

  memset(dp, -1, sizeof(dp));
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    // cout << "x = " << x << ", grundy = " << rec(x) << '\n';
    ans ^= rec(x);
  }
  cout << (ans ? "First" : "Second") << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
