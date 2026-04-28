#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;
  int N = S.size();
  if (S[N - 1] == '4') {
    for (S[N - 1] = '1'; S[N - 1] <= '3'; S[N - 1]++) cout << S << '\n';
    return;
  }

  int U[4]{};
  for (int i = 0;; i++) {
    if (S.size() == 1) break;

    int o = S.back() - '0'; S.pop_back();
    if (!U[o]) {
      U[o] = 1;
      cout << S + '4' << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
