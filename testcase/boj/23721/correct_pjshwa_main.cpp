#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int a[MAX + 1], p[MAX + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 1; i < n; i++) {
    p[i] = p[i - 1];
    if (a[i] < a[i - 1]) p[i]++;
  }

  int q;
  cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    int s = p[r - 1] - p[l - 1];

    if (s == 0) cout << "1\n";
    else if (s == 1 && a[l - 1] > a[r - 1]) cout << "2\n";
    else cout << "3\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
