#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int s[MAX];

void solve() {
  int n, t;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> s[i];
  cin >> t;

  set<int> S;
  for (int i = 0; i < n; i++) S.insert(s[i] / t);
  cout << S.size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
