#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;
  S = S.substr(2);

  cout << "YES\n";
  cout << stoi(S) << " 1";
  for (int i = 0; i < S.size(); i++) cout << "0";
  cout << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
