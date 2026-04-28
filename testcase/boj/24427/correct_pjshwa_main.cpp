#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  string s;
  cin >> n >> s;

  vector<int> L, R;
  int MID = 0;

  for (int i = 0; i < n; i++) {
    if (s[i] == 'L') {
      R.push_back(MID);
      MID = i + 1;
    }
    else {
      L.push_back(MID);
      MID = i + 1;
    }
  }
  R.push_back(MID);
  reverse(R.begin(), R.end());
  for (int e : L) cout << e << " ";
  for (int e : R) cout << e << " ";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
