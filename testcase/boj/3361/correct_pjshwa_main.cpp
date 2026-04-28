#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;
  deque<char> dq;
  for (char c : S) dq.push_back(c);
  while (!dq.empty() && dq.front() == 'L') dq.pop_front();
  while (!dq.empty() && dq.back() == 'R') dq.pop_back();
  if (dq.empty()) return cout << "0 0\n", void();

  ll N = dq.size(), rc = 0, swap_cnt = 0;
  for (int i = 0; i < N; ++i) {
    if (dq[i] == 'L') swap_cnt += rc;
    else ++rc;
  }

  int iter = 0; rc = 0;
  for (int i = 0; i < N; ++i) {
    if (dq[i] == 'L') ++iter, --rc;
    else if (rc > 0) ++iter;
    else ++rc;
  }

  cout << iter << ' ' << swap_cnt << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
