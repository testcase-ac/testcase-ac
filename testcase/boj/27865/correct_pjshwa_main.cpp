#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool ask(int x) {
  cout << "? " << x << endl;
  string ret; cin >> ret;
  return ret == "Y";
}

void solve() {
  int N; cin >> N;
  while (!ask(1)) {}
  cout << "! 1" << endl;
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
