#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int bits[30][MAX];

void solve() {
  int n, x;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> x;
    int b = 0;
    while (x) {
      if (x & 1) bits[b][i] = 1;
      x >>= 1;
      b++;
    }
  }

  int ml = 0;
  for (int b = 0; b < 30; b++) {
    int cl = 0;
    for (int i = 0; i < n; i++) if (bits[b][i]) cl++;
    ml = max(ml, cl);
  }
  cout << ml << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
