#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50;
int a[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  int last, cnt;

  last = 0, cnt = 0;
  for (int i = 0; i < n; i++) {
    if (a[i] > last) {
      cnt++;
      last = a[i];
    }
  }
  cout << cnt << '\n';

  last = 0, cnt = 0;
  for (int i = n - 1; i >= 0; i--) {
    if (a[i] > last) {
      cnt++;
      last = a[i];
    }
  }
  cout << cnt << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
