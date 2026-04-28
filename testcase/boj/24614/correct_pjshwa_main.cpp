#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 18;
int P[MAX + 1][MAX + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) cin >> P[i][j];
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
