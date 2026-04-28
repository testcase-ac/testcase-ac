#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX], wstart[MAX], wend[MAX];

void solve() {
  int n, c;
  cin >> n >> c;
  for (int i = 0; i < n; i++) cin >> a[i];

  int e = 0, psum = 0, wcnt = 0;
  for (int s = 0; s < n; s++) {
    while (e < n && psum + a[e] <= c) {
      psum += a[e];
      wstart[e++] = ++wcnt;
    }

    psum -= a[s];
    wend[s] = ++wcnt;
  }

  for (int i = 0; i < n; i++) cout << wend[i] - wstart[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
