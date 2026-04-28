#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  map<string, string> M = {
    {"M", "MatKor"},
    {"W", "WiCys"},
    {"C", "CyKor"},
    {"A", "AlKor"},
    {"$", "$clear"}
  };

  string S; cin >> S;
  cout << M[S] << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
