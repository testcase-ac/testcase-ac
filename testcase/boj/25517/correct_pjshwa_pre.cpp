#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MOD = 1e9 + 7;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N = 1e9;
  // cin >> N;

  cout << "int pre[1000] = {";
  ll cur = 1;
  for (int i = 1; i <= N; i++) {
    cur = (cur * i) % MOD;
    if (i % 1'000'000 == 0) {
      cout << cur;
      if (i < N) cout << ',';
    }
  }
  cout << "};" << endl;
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
