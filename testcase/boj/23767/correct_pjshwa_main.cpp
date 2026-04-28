#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int ask(string s) {
  cout << s << endl;

  string X; cin >> X >> X;
  if (X == "GRANTED") exit(0);
  cin >> X;
  int ret = stoi(X.substr(1));
  cin >> X;
  return ret;
}

void solve() {
  vector<char> Q;
  for (char c = 'A'; c <= 'Z'; c++) Q.push_back(c);
  for (char c = 'a'; c <= 'z'; c++) Q.push_back(c);
  for (char c = '0'; c <= '9'; c++) Q.push_back(c);

  string O = "A"; int len;
  for (len = 1; len <= 20; len++) {
    if (ask(O) != 5) break;
    O += 'A';
  }

  for (int i = 0; i < len; i++) {
    char mc = 0; int v = 0;
    for (char c : Q) {
      O[i] = c;
      int r = ask(O);
      if (r > v) v = r, mc = c;
    }

    assert(mc != 0);
    O[i] = mc;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
