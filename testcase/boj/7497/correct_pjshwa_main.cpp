#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

string S;
int z;
ll d[20][2][2];

// current digit, following original number, leading non-zero not appeared
ll r(int i, bool f, bool l) {
  if (d[i][f][l] != -1) return d[i][f][l];
  if (i == z) return d[i][f][l] = 1;

  ll ret = 0;
  if (f) {
    int c = S[i] - '0';
    for (int u = 0; u <= c; u++) {
      ll m = (l && u == 0) ? 1 : u;
      ret = max(ret, m * r(i + 1, u == c, l && u == 0));
    }
  }
  else {
    for (int u = 0; u < 10; u++) {
      ll m = (l && u == 0) ? 1 : u;
      ret = max(ret, m * r(i + 1, 0, l && u == 0));
    }
  }

  return d[i][f][l] = ret;
}

void solve() {
  cin >> S;
  z = S.size();

  memset(d, -1, sizeof(d));
  cout << r(0, 1, 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
