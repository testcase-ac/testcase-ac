#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int h[50];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < 50; i++) {
    if (h[i] > n) return cout << i << '\n', void();
  }
}

int main() {
  fast_io();

  h[0] = 1, h[1] = 2;
  for (int i = 2; i < 50; i++) {
    h[i] = h[i - 1] + h[i - 2] + 1;
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
