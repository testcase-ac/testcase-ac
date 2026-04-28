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

const int MAXN = 200;
int C[MAXN + 1];
int dp[MAXN + 1][MAXN + 1];

int rec(int s, int e) {
  if (s > e) return 0;
  if (dp[s][e] != -1) return dp[s][e];

  vector<int> Gs;
  for (int i = s; i <= e; ++i) {
    int j = i + C[i];
    if (j > e) continue;
    Gs.push_back(rec(s, i - 1) ^ rec(j + 1, e));
  }
  compress(Gs);

  // calculate mex of Gs
  int mex = 0;
  for (int g : Gs) {
    if (g == mex) ++mex;
  }
  return dp[s][e] = mex;
}

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> C[i];

  memset(dp, -1, sizeof dp);
  int ans = rec(1, N);
  if (ans == 0) cout << "-1\n";
  else {
    int i = 1;
    for (; i <= N; ++i) {
      int j = i + C[i];
      if (j > N) continue;
      if ((rec(1, i - 1) ^ rec(j + 1, N)) == 0) break;
    }
    cout << i << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
