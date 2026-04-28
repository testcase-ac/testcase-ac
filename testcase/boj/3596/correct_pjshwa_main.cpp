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

int rec(int i) {
  if (i <= 0) return 0;
  if (dp[i] != -1) return dp[i];

  vector<int> Gs;
  for (int j = 0; j < i; ++j) {
    int cur = rec(j - 2) ^ rec(i - j - 3);
    Gs.push_back(cur);
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
  int N; cin >> N;
  memset(dp, -1, sizeof dp);
  cout << 2 - (rec(N) != 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
