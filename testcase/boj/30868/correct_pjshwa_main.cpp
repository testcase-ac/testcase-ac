#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  for (int t = 0; t < N / 5; ++t) cout << "++++ ";
  for (int t = 0; t < N % 5; ++t) cout << "|";
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
