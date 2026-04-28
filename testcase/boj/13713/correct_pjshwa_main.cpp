#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

vector<int> Z(string& s) {
  int n = s.size(), l = 0, r = 0;
  vector<int> zbox(n); zbox[0] = n;
  for (int i = 1; i < n; ++i) {
    if (i < r) zbox[i] = min(r - i, zbox[i - l]);
    while (i + zbox[i] < n && s[zbox[i]] == s[i + zbox[i]]) ++zbox[i];
    if (i + zbox[i] > r) l = i, r = i + zbox[i];
  }
  return zbox;
}

void solve() {
  string S; int M; cin >> S >> M;
  reverse(S.begin(), S.end());

  auto zbox = Z(S);
  while (M--) {
    int i; cin >> i;
    cout << zbox[S.size() - i] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
