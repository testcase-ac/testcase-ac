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

const int MAXN = 1e5;
int dp[MAXN + 1];

int rec(int w) {
  if (w <= 2) return 0;
  if (dp[w] != -1) return dp[w];

  vector<int> Gs;
  for (int i = 2; i < w; ++i) {
    int g = rec(i - 1) ^ rec(w - i);
    Gs.push_back(g);
  }
  compress(Gs);

  // calculate mex of Gs
  int mex = 0;
  for (int g : Gs) {
    if (g == mex) ++mex;
    else break;
  }
  return dp[w] = mex;
}

void solve() {
  int N, M; cin >> N >> M;

  memset(dp, -1, sizeof dp);
  for (int i = 1; i <= 100; ++i) dp[i] = rec(i);
  for (int i = 101; i <= MAXN; ++i) dp[i] = dp[i - 34];

  if (!dp[N] && !dp[M]) cout << "hs\n";
  else cout << "sh\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
