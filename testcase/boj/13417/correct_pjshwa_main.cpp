#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  deque<string> dq;
  string s0; cin >> s0; dq.push_back(s0);
  for (int i = 1; i < N; i++) {
    string s; cin >> s;
    if (s <= dq.front()) dq.push_front(s);
    else dq.push_back(s);
  }

  for (auto& s : dq) cout << s;
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
