#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, MOD = 998244353;
string B = ""; int N, K;
int d[MAX + 1][MAX + 1][2];

// index, 1 used, following max
int r(int i, int u, bool f) {
  if (i == N) return u == K;
  if (d[i][u][f] != -1) return d[i][u][f];

  int res = 0;
  if (f) {
    if (B[i] == '0') {
      res = (res + r(i + 1, u, f)) % MOD;
    }
    else {
      res = (res + r(i + 1, u, !f)) % MOD;
      if (u < K) res = (res + r(i + 1, u + 1, f)) % MOD;
    }
  }
  else {
    res = (res + r(i + 1, u, f)) % MOD;
    if (u < K) res = (res + r(i + 1, u + 1, f)) % MOD;
  }

  return d[i][u][f] = res;
}

string x2b(char c) {
  if (c == '0') return "0000";
  if (c == '1') return "0001";
  if (c == '2') return "0010";
  if (c == '3') return "0011";
  if (c == '4') return "0100";
  if (c == '5') return "0101";
  if (c == '6') return "0110";
  if (c == '7') return "0111";
  if (c == '8') return "1000";
  if (c == '9') return "1001";
  if (c == 'A') return "1010";
  if (c == 'B') return "1011";
  if (c == 'C') return "1100";
  if (c == 'D') return "1101";
  if (c == 'E') return "1110";
  if (c == 'F') return "1111";
}

void solve() {
  string S;
  cin >> S >> K;
  for (char& c : S) B += x2b(c);
  N = B.size();

  memset(d, -1, sizeof(d));
  cout << r(0, 0, true) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
