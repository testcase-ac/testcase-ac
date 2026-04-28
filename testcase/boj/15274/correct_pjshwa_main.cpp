#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S;
  cin >> N >> S;

  map<int, int> t;
  int cnt = 0;
  for (ll i = 2; i * i <= N; ++i) {
    while (N % i == 0) {
      t[i]++;
      cnt++;
      N /= i;
    }
  }
  if (N > 1) {
    t[N]++;
    cnt++;
  }

  bool v_same = true;
  int pv = -1;
  for (auto& [k, v] : t) {
    if (pv == -1) pv = v;
    else if (pv != v) v_same = false;
  }

  if (cnt & 1) {
    int lim = (cnt - 1) / 2;
    for (auto& [k, v] : t) {
      if (v_same) {
        if (v < lim + 1) return cout << "tie\n", void();
      }
      else {
        if (v < lim) return cout << "tie\n", void();
      }
    }
    cout << S << '\n';
  }
  else {
    int lim = cnt / 2;
    for (auto& [k, v] : t) {
      if (v < lim) return cout << "tie\n", void();
    }
    if (S == "Alice") cout << "Bob\n";
    else cout << "Alice\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
