#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N;
  cin >> N;
  vector<int> A(N);
  map<int, int> pt;
  set<int> u;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    if (A[i] <= N) {
      if (pt.count(A[i])) return cout << "0\n", void();
      pt[A[i]] = i;
    }
    if (u.count(A[i])) return cout << "0\n", void();
    u.insert(A[i]);
  }

  int last = -1;
  for (auto& [k, v] : pt) {
    if (last != -1) {
      int diff = (v + N - pt[last]) % N;
      if (k - last != diff) return cout << "0\n", void();
    }
    last = k;
  }

  cout << "1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
