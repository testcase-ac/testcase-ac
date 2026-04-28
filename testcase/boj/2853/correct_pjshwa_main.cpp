#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];

  vector<int> rems;
  for (int i = 1; i < N; i++) {
    int diff = A[i] - A[0], f = 1;
    for (int r : rems) {
      if (diff % r == 0) f = 0;
    }
    if (f) rems.push_back(diff);
  }

  cout << rems.size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
