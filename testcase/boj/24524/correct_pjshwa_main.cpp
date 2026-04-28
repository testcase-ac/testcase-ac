#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
vector<int> p[26];
int c[26];

void solve() {
  string s, t;
  cin >> s >> t;
  for (int i = 0; i < s.size(); i++) p[s[i] - 'a'].push_back(i);

  int ans = 0;
  while (1) {
    bool able = true;
    int lu = -1;
    for (char ch : t) {
      int cu = ch - 'a';
      while (c[cu] < p[cu].size() && p[cu][c[cu]] < lu) c[cu]++;

      if (c[cu] == p[cu].size()) {
        able = false;
        break;
      }
      else {
        lu = p[cu][c[cu]];
        c[cu]++;
      }
    }

    if (able) ans++;
    else break;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
