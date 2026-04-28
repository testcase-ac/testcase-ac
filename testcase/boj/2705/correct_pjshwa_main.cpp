#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
int d[MAX + 1];

void solve() {
  int N; cin >> N;
  cout << d[N] << '\n';
}

int main() {
  fast_io();

  d[1] = 1;
  for (int i = 2; i <= MAX; i++) {
    d[i] = 1;
    for (int j = 0; j <= i - 2; j++) {
      int v = i - j;
      if (v % 2 == 0) d[i] += d[v / 2];
    }
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
