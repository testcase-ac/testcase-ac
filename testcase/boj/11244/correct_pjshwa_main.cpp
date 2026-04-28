#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int Q;
  cin >> Q;
  unordered_map<string, int> t;

  while (Q--) {
    string S;
    cin >> S;

    if (S.size() == 10) {
      if (t.count(S)) {
        if (t[S] == 1) cout << "unique\n";
        else cout << "duplicate\n";
      }
      else cout << "not exist\n";
    }
    else {
      unordered_set<string> tmp;
      for (int i = 0; i < 35; i++) {
        string U = S.substr(i, 10);
        tmp.insert(U);
      }
      for (auto U : tmp) t[U]++;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
