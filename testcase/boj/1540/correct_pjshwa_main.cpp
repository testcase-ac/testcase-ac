#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int d[MAX + 1];

void solve() {
  int n;
  cin >> n;
  cout << d[n] << '\n';
}

int main() {
  fast_io();

  d[4] = 1;
  int nxt = 3, psq = 4;
  for (int i = 5; i <= MAX; i++) {
    if (i == nxt * nxt) {
      d[i] = d[psq] + psq;
      psq = nxt * nxt, nxt++;
    }
    else if (i >= psq + nxt) {
      d[i] = d[i - 1] + (i - psq - nxt);
    }
    else {
      d[i] = d[i - 1] + (i - psq - 1);
    }
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
