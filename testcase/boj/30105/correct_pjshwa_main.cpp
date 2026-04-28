#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
} 

void solve() {
  int N; cin >> N;

  set<int> A;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    A.insert(x);
  }

  vector<int> diffs;
  int base = *A.begin();
  for (int x : A) {
    if (x != base) diffs.push_back(x - base);
  }

  vector<int> candidates;
  for (int diff : diffs) {
    bool ok = true;
    for (int x : A) {
      if (A.count(x + diff) || A.count(x - diff)) continue;
      ok = false;
    }
    if (ok) candidates.push_back(diff);
  }

  cout << candidates.size() << '\n';
  for (int x : candidates) cout << x << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
