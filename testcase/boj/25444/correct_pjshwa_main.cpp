#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool ask_if_palindrome(int l, int r) {
  cout << "? " << l << " " << r << endl;
  int ret; cin >> ret;
  return ret;
}

void solve() {
  int N; cin >> N;
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
