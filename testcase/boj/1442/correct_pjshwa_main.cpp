#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int d[100][3][3][2];
string S; int N;

int r(int i, int l1, int l2, int f) {
  if (d[i][l1][l2][f] != -1) return d[i][l1][l2][f];
  if (i == N) return 1;

  int ret = 0;
  for (int c = 0; c < 2; c++) {
    if (f && c > S[i] - '0') break;
    if (l1 != 2 && l1 == l2 && l2 == c) continue;

    int nc = l2 == 2 && c == 0 ? 2 : c;
    ret += r(i + 1, l2, nc, f && c == S[i] - '0');
  }
  return d[i][l1][l2][f] = ret;
}

string to_binary_string(int n) {
  string ret;
  while (n) {
    ret.push_back(n % 2 + '0');
    n /= 2;
  }
  reverse(ret.begin(), ret.end());
  return ret;
}

int f(int n) {
  if (n <= 6) return 0;

  memset(d, -1, sizeof(d));
  S = to_binary_string(n); N = S.size();
  return n - r(0, 2, 2, 1) + 1;
}

void solve() {
  int L, R; cin >> L >> R;
  cout << f(R) - f(L - 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
