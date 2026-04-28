#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<int> ops(N);
  for (auto& x : ops) cin >> x;

  stack<int> S;
  for (auto& x : ops) {
    if (x == 1) S.push(x);
    else {
      while (!S.empty() && S.top() != x - 1) S.pop();
      if (S.empty()) return cout << "NO\n", void();
      S.pop(); S.push(x);
    }
  }
  cout << "YES\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
