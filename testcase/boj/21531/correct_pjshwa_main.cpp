#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 10000, MOD = 1e9 + 7;
string S;
int z;
int d[MAX + 1][2][11][11];

int r(int i, int carry, int l1, int l2) {
  if (i == z) return d[i][carry][l1][l2] = (
    carry == 0 && l1 != 0 && l2 != 0
  );
  if (d[i][carry][l1][l2] != -1) return d[i][carry][l1][l2];

  int ret = 0;
  for (int d1 = 0; d1 < 10; d1++) {
    if (d1 == l1) continue;
    
    int d2 = (S[i] - '0') - d1 - carry, ncarry = 0;
    if (d2 < 0) {
      d2 += 10;
      ncarry = 1;
    }
    if (d2 == l2) continue;

    ret = (ret + r(i + 1, ncarry, d1, d2)) % MOD;
  }

  return d[i][carry][l1][l2] = ret;
}

void solve() {
  cin >> S;
  z = S.size();
  reverse(S.begin(), S.end());

  memset(d, -1, sizeof(d));
  cout << r(0, 0, 10, 10) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
