#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    if (x == 300) cout << "1 ";
    else if (x >= 275) cout << "2 ";
    else if (x >= 250) cout << "3 ";
    else cout << "4 ";
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
