#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;
string comp[26];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    string s, o;
    cin >> s >> o;
    comp[o[0] - 'A'] = s;
  }

  string cs;
  int s, e;
  cin >> cs >> s >> e;
  s--; e--;
  for (char c : cs) {
    int ci = c - 'A';
    for (int i = 0; i < comp[ci].size(); i++) {
      if (s <= i && i <= e) cout << comp[ci][i];
    }
    s -= comp[ci].size();
    e -= comp[ci].size();
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
