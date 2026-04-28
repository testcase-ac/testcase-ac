#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int nw[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

string to_str(int n) {
  string s;
  if (n >= 10) return to_string(n);
  return "0" + to_string(n);
}

void solve() {
  int n;
  cin >> n;
  for (int a = 0; a <= 99; a++) for (int b = 0; b <= 99; b++) {
    int c = a + b;
    if (c >= 100) continue;

    int aneed = nw[a % 10] + nw[a / 10], bneed = nw[b % 10] + nw[b / 10];
    int cneed = nw[c % 10] + nw[c / 10];
    if (aneed + bneed + cneed + 4 == n) {
      cout << to_str(a) << '+' << to_str(b) << '=' << to_str(c) << '\n';
      return;
    }
  }
  cout << "impossible\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
