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

const int MAXN = 1000;
int L, K, C[MAXN + 1], dp[MAXN + 1];

int rec(int i) {
  if (dp[i] != -1) return dp[i];

  vector<int> Gs;
  for (int r = 0; r <= min(i - 1, K); ++r) {
    int top = i - r;
    if (top < C[top]) continue;
    Gs.push_back(rec(top - C[top]));
  }
  compress(Gs);

  // calculate mex of Gs
  int mex = 0;
  for (int g : Gs) {
    if (g == mex) ++mex;
  }
  return dp[i] = mex;
}

void solve() {
  int N, ans = 0; cin >> N >> K;
  for (int i = 0; i < N; ++i) {
    cin >> L;
    for (int j = 1; j <= L; ++j) cin >> C[j];
    memset(dp, -1, sizeof dp);
    ans ^= rec(L);
  }
  if (ans) cout << "Alice can win.\n";
  else cout << "Bob will win.\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
