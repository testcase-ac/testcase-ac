#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, U, L; cin >> N >> U >> L;

  if (N >= 1000) {
    if (U >= 8000 || L >= 260) cout << "Very ";
    cout << "Good\n";
  }
  else cout << "Bad\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
