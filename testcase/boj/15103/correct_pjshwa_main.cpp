#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

string S;
int N;
ll dp[20][2][2][2];

ll rec(int i, int z, int o, int f) {
  if (dp[i][z][o][f] != -1) return dp[i][z][o][f];
  if (i == N) return z == 0;

  ll ret = 0;
  for (int c = 0; c < 10; ++c) {
    if (f && c > S[i] - '0') break;
    if (z) {
      if (c == 0) ret += rec(i + 1, z, o, f && c == S[i] - '0');
      else if (c % 2 == 1) ret += rec(i + 1, 0, i & 1, f && c == S[i] - '0');
    }
    else if (((i + o) & 1) ^ (c & 1)) {
      ret += rec(i + 1, 0, o, f && c == S[i] - '0');
    }
  }
  return dp[i][z][o][f] = ret;
}

ll upto(ll n) {
  if (n == 0) return 0;
  S = to_string(n); N = S.size();

  memset(dp, -1, sizeof(dp));
  return rec(0, 1, 0, 1);
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
