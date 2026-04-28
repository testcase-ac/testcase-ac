#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int a[MAX], d[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  int e = 0;
  for (int i = 0; i < n; i++) {
    d[i] = a[i];
    for (int j = 0; j < i; j++) {
      if (a[j] > a[i] && d[i] < d[j] + a[i]) {
        d[i] = d[j] + a[i];
      }
    }
    if (e < d[i]) e = d[i];
  }
  cout << e << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
