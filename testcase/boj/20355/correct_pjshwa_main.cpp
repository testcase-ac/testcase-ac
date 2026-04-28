#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;

  set<int> U;
  for (char& c : S) U.insert((26 + c - 'i') % 26);

  int ans = 26 - U.size();
  if (ans == 0) cout << "impossible\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
