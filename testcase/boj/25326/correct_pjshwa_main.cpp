#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e4;

void solve() {
  int n, m;
  cin >> n >> m;
  vector<tuple<string, string, string>> S(n);
  for (int i = 0; i < n; i++) {
    string s, f, c;
    cin >> s >> f >> c;
    S[i] = {s, f, c};
  }

  while (m--) {
    string s, f, c;
    cin >> s >> f >> c;

    int cnt = 0;
    for (int i = 0; i < n; i++) {
      auto [cs, cf, cc] = S[i];
      bool r = true;

      r &= (s == "-" || cs == s);
      r &= (f == "-" || cf == f);
      r &= (c == "-" || cc == c);
      if (r) cnt++;
    }
    cout << cnt << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
