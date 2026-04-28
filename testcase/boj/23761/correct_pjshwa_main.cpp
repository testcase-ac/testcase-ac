#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

string ask(int a, int b) {
  cout << "? " << a << ' ' << b << endl;
  string ret; cin >> ret;
  return ret;
}

void solve() {
  int n; cin >> n;

  for (int s = 0; s < (n + 1) / 2; s++) {
    int a = 2 * s + 1, b = a + 1;
    if (s < (n - 1) / 2 && ask(a, b) == "equal") continue;

    int o = 1;
    if (s == 0) o = 3;

    if (ask(a, o) == "equal") cout << "! " << b << endl;
    else cout << "! " << a << endl;
    break;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
