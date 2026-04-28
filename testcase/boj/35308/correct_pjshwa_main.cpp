#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; cin >> N >> K;
  if (N == 1 && K == 1) return cout << "1\n", void();
  if (K != 2) return cout << "-1\n", void();
  for (int i = 2; i <= N; ++i) cout << i << ' ';
  cout << "1\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
