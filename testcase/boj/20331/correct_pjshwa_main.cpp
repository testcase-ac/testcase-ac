#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e4;
int a[MAX], r[MAX];

void solve() {
  int n, p; cin >> n >> p;
  for (int i = 0; i < n; i++) cin >> a[i];

  r[n - 1] = a[n - 1] == 0 ? 0 : 1;
  for (int i = n - 2; i >= 0; i--) {
    r[i] = r[i + 1];
    if (a[i] > a[i + 1]) r[i]++;
  }

  if (r[0] == 0 || r[0] == p) {
    for (int i = 0; i < n; i++) cout << r[i] << '\n';
  }
  else cout << "ambiguous\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
