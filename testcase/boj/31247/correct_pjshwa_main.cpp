#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, K; cin >> N >> K;
  if (K > 60) cout << "0\n";
  else {
    ll pw = 1;
    for (int i = 0; i < K; ++i) pw *= 2;
    cout << N / pw - N / (2 * pw) << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
