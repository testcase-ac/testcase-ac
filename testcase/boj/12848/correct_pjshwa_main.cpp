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
int dp[MAXN + 1];
char board[MAXN + 1][MAXN + 1];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> board[i];

  int K; cin >> K;
  vector<int> W(K);
  for (auto& w : W) cin >> w;

  for (int i = 1; i <= M; ++i) {
    unordered_set<int> Gs;
    for (int w : W) {
      if (w > i) break;
      for (int l = 0; l <= i - w; ++l) {
        int r = i - w - l;
        if (l > r) break;
        Gs.insert(dp[l] ^ dp[r]);
      }
    }

    // calculate mex of Gs
    int mex = 0;
    while (Gs.count(mex)) ++mex;
    dp[i] = mex;
  }

  int ans = 0;
  for (int i = 0; i < N; ++i) {
    int streak = 0;
    for (int j = 0; j < M; ++j) {
      if (board[i][j] == '.') ++streak;
      else {
        ans ^= dp[streak];
        streak = 0;
      }
    }
    ans ^= dp[streak];
  }

  if (ans) cout << "nein\n";
  else cout << "hyo123bin\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
