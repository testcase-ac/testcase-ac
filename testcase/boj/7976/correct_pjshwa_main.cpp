#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int t[MAX][2], d[MAX][2], a[MAX];

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    a[i] = (a[i] & 1);

    t[i % k][a[i]]++;
  }

  d[0][0] = t[0][1];
  d[0][1] = t[0][0];
  for (int i = 1; i < k; i++) {
    d[i][0] = min(d[i - 1][0] + t[i][1], d[i - 1][1] + t[i][0]);
    d[i][1] = min(d[i - 1][0] + t[i][0], d[i - 1][1] + t[i][1]);
  }

  cout << d[k - 1][0] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
