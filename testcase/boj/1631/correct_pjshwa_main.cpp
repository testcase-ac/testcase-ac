#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 30;
int m, a[MAX + 1], w[MAX + 1];

void r(int i) {
  if (i == 0) return;

  int from = a[i], to = w[i];
  if (from == to) r(i - 1);
  else {
    int mid = 3 - from - to;
    if (m >= 1 << (i - 1)) {
      for (int j = 1; j < i; j++) a[j] = mid;
      a[i] = to;
      m -= 1 << (i - 1);
    }
    else {
      for (int j = 1; j < i; j++) w[j] = mid;
    }
    r(i - 1);
  }
}

void solve() {
  int n; string s;
  cin >> n >> m >> s;
  for (int i = 1; i <= n; i++) w[i] = s[i - 1] - 'A';

  r(n);

  for (int i = 1; i <= n; i++) cout << (char)(a[i] + 'A');
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
