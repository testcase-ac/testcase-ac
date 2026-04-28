#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void print(int N) {
  int q = sqrt(N);
  for (int i = 0; i < q; i++) cout << 'A';
  for (char c = 'B'; c <= 'Y'; c++) cout << c;
  for (int i = 0; i < q; i++) cout << 'Z';

  if (q * q != N) print(N - q * q);
}

void solve() {
  int N;
  cin >> N;
  print(N);
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
