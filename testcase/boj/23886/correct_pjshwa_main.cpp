#include <bits/stdc++.h>
using namespace std;

const int MAX = 5e5;
int a[MAX];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool alpsoo(string s) {
  int n = s.size();
  if (s[0] > s[1] || s[n - 1] > s[n - 2]) return false;

  int pslope = 0;
  for (int i = 0; i < n - 1; i++) {
    if (s[i] == s[i + 1]) return false;
    int cslope = s[i + 1] - s[i];

    if (pslope * cslope > 0 && pslope != cslope) return false;
    pslope = cslope;
  }
  return true;
}

void solve() {
  string s;
  cin >> s;

  if (alpsoo(s)) cout << "ALPSOO\n";
  else cout << "NON ALPSOO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
