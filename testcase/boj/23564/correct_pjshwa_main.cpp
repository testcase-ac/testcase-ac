#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S;
  cin >> S;

  string pat = "";
  vector<pair<char, int>> ans;
  while (1) {
    char nchar = S[pat.size()];
    string f = pat + nchar;

    int sz = f.size(), rep;
    for (int i = 0;; i++) {
      if (S.substr(i * sz, sz) != f) {
        rep = i;
        break;
      }
    }

    if (rep == 0) break;
    ans.push_back({nchar, rep});

    string npat = "";
    for (int i = 0; i < rep; i++) npat += f;
    npat += pat;
    pat = npat;
  }

  for (auto [c, r] : ans) cout << c;
  cout << '\n';
  for (auto [c, r] : ans) cout << r << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
