#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 50;
int a[MAX + 1], d[MAX + 1][MAX + 1];

int n;
void solve() {
  for (int i = 1; i <= n; ++i) cin >> a[i];
}

int main() {
  fast_io();

  while (cin >> n) {
    if (n == 0) break;
    solve();
  }
}
