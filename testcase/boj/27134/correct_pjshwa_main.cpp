#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 1000;
ll d[MAXV + 1];

void solve() {
  int N;
  cin >> N;

  d[0] = 1; ll sum = 0;
  for (int i = 1; i <= N; i++) {
    sum += i;

    for (int v = MAXV; v >= i; v--) d[v] += d[v - i];
  }

  if (sum & 1) cout << "0\n";
  else cout << d[sum / 2] / 2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
