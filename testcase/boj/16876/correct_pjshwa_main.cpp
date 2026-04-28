#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int d[10000][101];
int n, m;

bool r(string s, int t) {
  int x = stoi(s);
  if (d[x][t] != -1) return d[x][t];

  if (t == m) return d[x][t] = x <= n;
  else {
    bool res;

    if (t & 1) {
      res = 0;

      for (int i = 0; i < 4; i++) {
        string u = s;

        if (u[i] == '9') u[i] = '0';
        else u[i]++;

        if (r(u, t + 1)) res = 1;
      }
    }
    else {
      res = 1;

      for (int i = 0; i < 4; i++) {
        string u = s;

        if (u[i] == '9') u[i] = '0';
        else u[i]++;

        if (!r(u, t + 1)) res = 0;
      }
    }

    return d[x][t] = res;
  }
}

void solve() {
  string s;
  cin >> s >> m;
  n = stoi(s);

  memset(d, -1, sizeof(d));

  if (r(s, 0)) cout << "cubelover\n";
  else cout << "koosaga\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
