#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cout << i + 1 << ' ';
    if (i != N - 1 && i % 6 == 5) cout << "Go! ";
  }
  cout << "Go!\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
