#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll L[128], C[128];

void solve() {
  int n; string s;
  cin >> n >> s;

  memset(L, 0, sizeof(L));
  memset(C, 0, sizeof(C));

  ll O = 0;
  for (int i = 0; i < n; i++) L[s[i]] = i, C[s[i]]++;
  for (int i = 0; i < n; i++) O += L[s[i]] - i;

  ll E = 0;
  for (int i = 0; i < 128; i++) E += C[i] * (C[i] - 1) / 2;

  cout << 5 * (O - E) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
