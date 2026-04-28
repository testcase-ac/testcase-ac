#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  vector<pii> O, E;
  for (int i = 0; i < N; ++i) {
    string S; cin >> S;
    int Z = S.size(), odd = 0, even = 0;
    for (int j = 0; j < Z; ++j) {
      if (S[j] == 'G') continue;
      j % 2 ? ++odd : ++even;
    }
    if (Z % 2) O.emplace_back(odd, even);
    else E.emplace_back(odd, even);
  }

  int ans = 0;
  if (O.empty()) {
    for (auto& [odd, even] : E) ans += even;
  }
  else {
    for (auto& [odd, even] : E) ans += max(odd, even);

    priority_queue<int> pq;
    for (auto& [odd, even] : O) {
      ans += even;
      pq.emplace(odd - even);
    }
    for (int i = 1; i < (int)O.size(); i += 2) {
      ans += pq.top();
      pq.pop();
    }
  }
  cout << ans << '\n';
  
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
