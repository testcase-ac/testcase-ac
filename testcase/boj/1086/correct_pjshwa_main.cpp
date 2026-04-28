#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

string ss[15];
int a[15], l[15], pw[51];
ll d[1 << 15][100];
int main() {
  fast_io();

  int n, k;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> ss[i];
  cin >> k;
  for (int i = 0; i < n; i++) {
    int ai = 0, p = 1, sz = ss[i].size();
    for (int j = sz - 1; j >= 0; j--) {
      int d = ss[i][j] - '0';
      ai = (ai + d * p) % k;
      p = (p * 10) % k;
    }
    a[i] = ai;
    l[i] = sz;
  }

  pw[0] = 1;
  for (int i = 1; i <= 50; i++) pw[i] = (pw[i - 1] * 10) % k;

  d[0][0] = 1;
  for (int state = 0; state < (1 << n); state++) {
    for (int m = 0; m < k; m++) {
      for (int ai = 0; ai < n; ai++) {
        if (state & (1 << ai)) continue;
        int nm = (m * pw[l[ai]] + a[ai]) % k;
        d[state | (1 << ai)][nm] += d[state][m];
      }
    }
  }

  ll nom = d[(1 << n) - 1][0], denom = 1;
  for (int i = 1; i <= n; i++) denom *= i;

  if (nom == 0) cout << "0/1";
  else {
    ll g = gcd(nom, denom);
    cout << nom / g << '/' << denom / g;
  }
}
