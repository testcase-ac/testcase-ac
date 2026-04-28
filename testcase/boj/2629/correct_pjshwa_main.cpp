#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int BIAS = 1.5e4, MAX = 3e4;
bool d[30][MAX + 20];

void solve() {
  int n, x;
  cin >> n;

  cin >> x;
  d[0][BIAS + x] = d[0][BIAS - x] = d[0][BIAS] = true;

  for (int i = 1; i < n; i++) {
    int x;
    cin >> x;
    for (int w = 0; w <= MAX; w++) {
      d[i][w] = d[i - 1][w];
      if (w + x <= MAX && d[i - 1][w + x]) d[i][w] = true;
      if (w >= x && d[i - 1][w - x]) d[i][w] = true;
    }
  }

  int q;
  cin >> q;
  while (q--) {
    int x;
    cin >> x;
    cout << (BIAS + x <= MAX && d[n - 1][BIAS + x] ? 'Y' : 'N') << ' ';
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
