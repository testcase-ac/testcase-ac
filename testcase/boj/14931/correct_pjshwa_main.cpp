#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int a[MAX + 1];

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];

  ll av = 0, ad = 0;
  for (int d = 1; d <= MAX; d++) {
    ll cv = 0;
    for (int l = d; l <= n; l += d) cv += a[l];
    if (cv > av) {
      av = cv;
      ad = d;
    }
  }

  cout << ad << ' ' << av << '\n';
}
