#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1e9 + 7;
stack<char> s;

void flush() {
  while (!s.empty()) {
    cout << s.top();
    s.pop();
  }
}

void solve() {
  string line;
  getline(cin, line);

  bool mode = 0;
  for (char& c : line) {
    if (c == ' ') {
      flush();
      cout << c;
      continue;
    }
    else if (c == '<') {
      flush();
      cout << c;
      mode = 1;
    }
    else if (c == '>') {
      cout << c;
      mode = 0;
    }
    else if (mode) {
      cout << c;
    }
    else {
      s.push(c);
    }
  }
  flush();
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
