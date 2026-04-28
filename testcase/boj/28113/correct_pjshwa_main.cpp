#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, A, B; cin >> N >> A >> B;
  if (N <= B) {
    if (A < B) cout << "Bus\n";
    else if (A > B) cout << "Subway\n";
    else cout << "Anything\n";
  }
  else cout << "Bus\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
