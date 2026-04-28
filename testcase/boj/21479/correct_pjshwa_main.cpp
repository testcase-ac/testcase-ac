#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  vector<string> A; string x;
  while (cin >> x) A.push_back(x);
  sort(A.begin(), A.end(), [](const string& a, const string& b) {
    return a + b > b + a;
  });
  for (auto& x : A) cout << x;
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
