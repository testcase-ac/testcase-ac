#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, k;
  string s;
  cin >> n >> s >> k;
  k = min(n, k);

  bool able = true;
  for (int i = 0; i < k; i++) if (s[n - 1 - i] == '1') able = false;

  cout << (able ? "YES" : "NO");
}
