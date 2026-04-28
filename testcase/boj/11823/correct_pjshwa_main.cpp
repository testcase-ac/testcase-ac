#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 3e7, MAXZ = 27;
vector<int> lp, pr;
int dp[MAXZ][MAXZ][2], Z, z; string S;

int rec(int i, int cnt, int f) {
  if (dp[i][cnt][f] != -1) return dp[i][cnt][f];
  if (i == Z) return dp[i][cnt][f] = cnt == z;

  int ret = 0;
  for (char c = '0'; c <= '1'; ++c) {
    if (f && S[i] < c) break;
    ret += rec(i + 1, cnt + (c == '1'), f && (S[i] == c));
  }
  return dp[i][cnt][f] = ret;
}

int upto(int N) {
  // S is binary representation of N
  S.clear();
  while (N) {
    S.push_back((N & 1) + '0');
    N >>= 1;
  }
  reverse(S.begin(), S.end());
  Z = S.size();
  memset(dp, -1, sizeof(dp));
  return rec(0, 0, 1);
}

void solve() {
  int N, K; cin >> N >> K;
  while (K--) {
    int x; cin >> x;
    if (x & 1) {
      auto it = upper_bound(pr.begin(), pr.end(), x - 1);
      if (it == pr.begin()) N -= 1;
      else {
        --it;
        N = min(MAXN, N + *it - 1);
      }
    }
    else {
      z = __builtin_popcount(x);
      N -= upto(N);
    }
  }
  cout << N << '\n';
}

int main() {
  fast_io();

  // Memory hack
  lp.resize(MAXN + 1);
  for (ll i = 2; i <= MAXN; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAXN; j++)
      lp[i * pr[j]] = pr[j];
  }
  lp.clear();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
