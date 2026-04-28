#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
string d[MAX + 1];
bitset<MAX + 1> f;

int main() {
  fast_io();

  string DEF = "()";
  d[2] = DEF, f[2] = 1;

  for (int i = 2; i <= MAX; i++) {
    if (i < MAX) {
      if (!f[i + 1]) d[i + 1] = "(" + d[i] + ")", f[i + 1] = 1;
      else {
        if (d[i + 1].size() < d[i].size() + 2) continue;
        else if (d[i + 1].size() == d[i].size() + 2) {
          bool sl = false;
          for (int u = 0; u < d[i + 1].size(); u++) {
            char c;
            if (u == 0) c = '(';
            else if (u == d[i + 1].size() - 1) c = ')';
            else c = d[i][u - 1];

            if (c < d[i + 1][u]) {
              sl = true;
              break;
            }
            if (c > d[i + 1][u]) {
              sl = false;
              break;
            }
          }
          if (sl) d[i + 1] = "(" + d[i] + ")";
        }
        else d[i + 1] = "(" + d[i] + ")";
      }
    }
    for (int j = 2 * i; j <= MAX; j += i) {
      if (j / i > i) break;
      if (f[j] && d[j / i].size() + d[i].size() > d[j].size()) continue;

      bool sl = false;
      for (int u = 0; u < d[j / i].size() + d[i].size(); u++) {
        char c1 = u >= d[j / i].size() ? d[i][u - d[j / i].size()] : d[j / i][u];
        char c2 = u >= d[i].size() ? d[j / i][u - d[i].size()] : d[i][u];

        if (c1 < c2) {
          sl = true;
          break;
        }
        if (c1 > c2) {
          sl = false;
          break;
        }
      }

      if (sl) {
        if (!f[j]) d[j] = d[j / i] + d[i], f[j] = 1;
        else {
          int z = d[j / i].size() + d[i].size();
          if (z < d[j].size()) d[j] = d[j / i] + d[i];
          else if (z == d[j].size()) {
            bool sl = false;
            for (int u = 0; u < z; u++) {
              char c = u >= d[j / i].size() ? d[i][u - d[j / i].size()] : d[j / i][u];

              if (c < d[j][u]) {
                sl = true;
                break;
              }
              if (c > d[j][u]) {
                sl = false;
                break;
              }
            }
          }
        }
      }
      else {
        if (!f[j]) d[j] = d[i] + d[j / i], f[j] = 1;
        else {
          int z = d[i].size() + d[j / i].size();
          if (z < d[j].size()) d[j] = d[i] + d[j / i];
          else if (z == d[j].size()) {
            bool sl = false;
            for (int u = 0; u < z; u++) {
              char c = u >= d[i].size() ? d[j / i][u - d[i].size()] : d[i][u];

              if (c < d[j][u]) {
                sl = true;
                break;
              }
              if (c > d[j][u]) {
                sl = false;
                break;
              }
            }
          }
        }
      }
    }
  }

  int q, x;
  cin >> q;
  while (q--) {
    cin >> x;
    cout << d[x] << '\n';
  }
}
