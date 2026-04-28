#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3000;
double d[MAX + 1][MAX + 1];

void solve() {
  int n, a, b;
  cin >> n >> a >> b;

  double ansa = 0, ansb = 0;

  memset(d, 0, sizeof(d));
  a++;
  d[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= i; j++) {
      // Person with ICPC card won this round!
      if (j) {
        int I = a - (j - 1), O = b - (i - j);
        if (I > 0 && O >= 0) {
          double prob = d[i - 1][j - 1] * (2.0 * I / (2.0 * I + O));
          d[i][j] += (prob - prob / I);
          ansa += prob / I;
        }
      }

      // Person with other payment method won this round!
      int I = a - j, O = b - (i - 1 - j);
      if (I >= 0 && O > 0) {
        double prob = d[i - 1][j] * O / (2.0 * I + O);
        d[i][j] += prob;
      }
    }
  }

  memset(d, 0, sizeof(d));
  a--; b++;
  d[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= i; j++) {
      // Person with ICPC card won this round!
      if (j) {
        int I = a - (j - 1), O = b - (i - j);
        if (I > 0 && O >= 0) {
          double prob = d[i - 1][j - 1] * (2.0 * I / (2.0 * I + O));
          d[i][j] += prob;
        }
      }

      // Person with other payment method won this round!
      int I = a - j, O = b - (i - 1 - j);
      if (I >= 0 && O > 0) {
        double prob = d[i - 1][j] * O / (2.0 * I + O);
        d[i][j] += (prob - prob / O);
        ansb += prob / O;
      }
    }
  }

  cout << fixed << setprecision(10) << ansa << '\n' << ansb << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
