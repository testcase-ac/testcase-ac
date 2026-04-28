#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5, MOD = 1e9 + 7;
int d[MAX + 1];

void solve() {
  int N; cin >> N;
  cout << d[N] << '\n';
}

int main() {
  fast_io();

  d[0] = 1, d[1] = 1;
  for (int i = 2; i <= MAX; i++) {
    d[i] = (d[i - 1] + d[i - 2]) % MOD;
  }
 
  int t = 1;
  cin >> t;
  while (t--) solve();
}
