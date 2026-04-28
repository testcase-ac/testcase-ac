#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;
  if (S == "fdsajkl;" || S == "jkl;fdsa") cout << "in-out\n";
  else if (S == "asdf;lkj" || S == ";lkjasdf") cout << "out-in\n";
  else if (S == "asdfjkl;") cout << "stairs\n";
  else if (S == ";lkjfdsa") cout << "reverse\n";
  else cout << "molu\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
