#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 20;
ll dp[MAXN][9][2];
string S; int Z;

ll rec(int i, int d, int f) {
  if (i == Z) return d > 0;
  if (dp[i][d][f] != -1) return dp[i][d][f];

  ll c = S[i] - '0', ret = 0;
  for (int x = 0; x < 9; ++x) {
    if (f && x > c) break;
    ret += rec(i + 1, (d + x) % 9, f && (x == c));
  }
  return dp[i][d][f] = ret;
}

ll upto(ll n) {
  if (n < 9) return n;

  memset(dp, -1, sizeof(dp));
  S = to_string(n); Z = S.size();
  return rec(0, 0, 1);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  ll L, R; cin >> L >> R;
  cout << upto(R) - upto(L - 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
