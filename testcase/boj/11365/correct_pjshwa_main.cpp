#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

string s;
void solve() {
  reverse(s.begin(), s.end());
  cout << s << '\n';
}

int main() {
  fast_io();

  while (1) {
    getline(cin, s);
    if (s == "END") break;
    solve();
  }
}
