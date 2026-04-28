#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_palindrome(int n) {
  string s = to_string(n);
  for (int i = 0; i < s.size() / 2; i++) {
    if (s[i] != s[s.size() - i - 1]) return false;
  }
  return true;
}

const int MAXN = 1e5;
int dp[MAXN + 1];

int rec(int n) {
  if (dp[n] != -1) return dp[n];

  int ret = 0;
  for (int v = 1; v <= n; ++v) {
    if (!is_palindrome(v)) continue;
    ret |= !rec(n - v);
  }
  return dp[n] = ret;
}

void solve() {
  // int N; cin >> N;
  // for (int i = 1; i <= N; ++i) {
  //   if (!rec(i)) cout << "i = " << i << " : " << "SK" << '\n';
  // }

  string S; cin >> S;
  cout << (S.back() == '0' ? "E" : "B") << '\n';
}

int main() {
  fast_io();

  // memset(dp, -1, sizeof(dp));
  int t = 1;
  cin >> t;
  while (t--) solve();
}
