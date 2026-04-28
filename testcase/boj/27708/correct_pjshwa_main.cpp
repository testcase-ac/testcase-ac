#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
int c[MAX];

void solve() {
  int n; cin >> n;
  for (int i = 0; i < n; ++i) cin >> c[i];
  sort(c, c + n); swap(c[0], c[1]);

  cout << n << '\n';
  for (int i = 0; i < n; ++i) cout << c[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t; cout << t << '\n';
  while (t--) solve();
}
