#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<int> A; int l = 1, r = N;
  while (l <= r) {
    A.push_back(l++);
    A.push_back(r--);
  }
  if (N & 1) A.pop_back();

  while (!A.empty()) {
    cout << A.back() << ' ';
    A.pop_back();
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
