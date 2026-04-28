#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

vector<int> P[26];

void solve() {
  string v, s;
  cin >> v >> s;

  for (int i = 0; i < s.size(); i++) {
    int x = s[i] - 'a';
    P[x].push_back(i);
  }

  int m = 0; set<int> S;
  for (int i = 0; i < s.size(); i++) {
    S.insert(s[i] - 'a');
    if (S.size() == v.size()) {
      m++;
      S.clear();
    }
  }
  m++;

  int q;
  cin >> q;
  while (q--) {
    string qs;
    cin >> qs;

    if (qs.size() != m) {
      cout << "0\n";
      continue;
    }

    bool f = false; int p = 0;
    for (int i = 0; i < m; i++) {
      int x = qs[i] - 'a';
      auto it = lower_bound(P[x].begin(), P[x].end(), p);
      if (it == P[x].end()) {
        f = true;
        break;
      }
      p = *it + 1;
    }

    cout << (f ? "1\n" : "0\n");
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
