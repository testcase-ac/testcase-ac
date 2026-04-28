#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string S;
  cin >> S;
  ll n = S.size(), zc = 0, val = 0;
  for (int i = n - 1; i >= 0; i--) {
    if (S[i] == '1') val += zc;
    else zc++;
  }

  if (val % 3) cout << "Alice\n";
  else cout << "Bob\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
