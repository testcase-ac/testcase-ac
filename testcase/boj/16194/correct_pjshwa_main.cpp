#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
int P[MAX + 1], d[MAX + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; i++) cin >> P[i];

  d[1] = P[1];
  for (int i = 2; i <= N; i++) {
    d[i] = P[i];
    for (int j = i - 1; j >= 1; j--) d[i] = min(d[i], d[j] + P[i - j]);
  }
  cout << d[N] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
