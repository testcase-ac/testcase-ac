#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int A, B; cin >> A >> B;
  if (A <= B) cout << "NO\n";
  else {
    int V = A - B;
    if (A < 2 * V || B < V) cout << "NO\n";
    else {
      vector<pii> ans;
      for (int i = 0; i < V - 1; ++i) {
        ans.emplace_back(2, 1);
        A -= 2; B -= 1;
      }
      ans.emplace_back(A, B);

      cout << "YES\n";
      cout << ans.size() << '\n';
      for (auto [a, b] : ans) {
        for (int i = 0; i < b; ++i) cout << "ab";
        cout << "a\n";
      }
    }

  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
