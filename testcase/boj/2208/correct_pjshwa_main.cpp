#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
ll pff[MAX + 1], d[MAX + 1];

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;

  for (int i = 1; i <= n; i++) cin >> pff[i];
  for (int i = 1; i <= n; i++) pff[i] += pff[i - 1];

  d[m] = pff[m];
  for (int i = m + 1; i <= n; i++) {
    d[i] = max(d[i - 1] + pff[i] - pff[i - 1], pff[i] - pff[i - m]);
  }
  cout << *max_element(d, d + n + 1) << '\n';
}
