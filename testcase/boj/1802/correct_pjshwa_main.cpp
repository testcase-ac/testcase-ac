#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

string S;
bool rec(int l, int r) {
  if (l == r) return true;

  int m = (l + r) / 2;
  for (int i = 0; i < m - l; i++) {
    if (S[l + i] == S[r - i]) return false;
  }
  return rec(l, m - 1);
}

void solve() {
  cin >> S;

  if (rec(0, S.size() - 1)) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
