#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int A, B, C; cin >> A >> B >> C;

  cout << A + B - C << '\n';
  cout << stoi(to_string(A) + to_string(B)) - C << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
