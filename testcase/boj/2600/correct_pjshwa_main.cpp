#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500;
int d[MAX + 1][MAX + 1];
int b1, b2, b3;

bool r(int a, int b) {
  if (d[a][b] != -1) return d[a][b];

  bool ret = false;
  for (int ded : {b1, b2, b3}) {
    if (ded <= a) ret |= !r(a - ded, b);
    if (ded <= b) ret |= !r(a, b - ded);
  }

  return d[a][b] = ret;
}

void solve() {
  cin >> b1 >> b2 >> b3;

  memset(d, -1, sizeof d);
  int Q = 5;
  while (Q--) {
    int k1, k2;
    cin >> k1 >> k2;

    bool res = r(k1, k2);
    if (res) cout << "A\n";
    else cout << "B\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
