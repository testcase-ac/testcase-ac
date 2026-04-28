#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, MOD = 1e9 + 9;
int d[MAX + 1];

void solve() {
  int N;
  cin >> N;

  d[1] = d[2] = 1;
  for (int i = 3; i <= N + 1; i++) d[i] = (d[i - 1] + d[i - 3]) % MOD;
  cout << d[N + 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
