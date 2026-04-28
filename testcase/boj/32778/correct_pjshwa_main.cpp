#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string line, sub = "-"; getline(cin, line);
  if (line.back() == ')') {
    line.pop_back(); sub = "";
    while (line.back() != '(') {
      sub.push_back(line.back());
      line.pop_back();
    }
    line.pop_back(); line.pop_back();
    reverse(sub.begin(), sub.end());
  }
  cout << line << '\n' << sub << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
