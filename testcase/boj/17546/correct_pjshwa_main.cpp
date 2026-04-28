#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, m; cin >> n >> m;

  vector<int> A, B;
  for (int i = 1; i <= m; ++i) {
    int u, v; cin >> u >> v;
    if (u < v) A.push_back(i);
    else B.push_back(i);
  }
  if (A.size() > B.size()) swap(A, B);

  cout << A.size() << '\n';
  for (auto& t : A) cout << t << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
