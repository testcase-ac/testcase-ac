#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;

  int len = S.size();
  int zero_cnt = 0, one_cnt = 0;
  for (char c : S) {
    if (c == '0') ++zero_cnt;
    if (c == '1') ++one_cnt;
  }

  if (zero_cnt == one_cnt) {
    if (S[0] == '0') {
      cout << '1';
      for (int i = 1; i < len; ++i) cout << '0';
    }
    else {
      cout << '0';
      for (int i = 1; i < len; ++i) cout << '1';
    }
  }
  else if (zero_cnt > one_cnt) {
    for (int i = 0; i < len; ++i) cout << '1';
  }
  else {
    for (int i = 0; i < len; ++i) cout << '0';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
