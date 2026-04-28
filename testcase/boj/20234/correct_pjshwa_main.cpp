#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

string ask(int i, int j) {
  cout << i << ' ' << j << endl;
  string ret;
  cin >> ret;

  if (ret == "WIN") exit(0);
  return ret;
}

void solve() {
  int n;
  cin >> n;
  while (1) {
    for (int i = 1; i < n; i++) ask(i, i + 1);
    for (int i = n - 1; i >= 1; i--) ask(i, i + 1);
  }
}

int main() {
  // fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
