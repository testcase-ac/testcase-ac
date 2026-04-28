#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int five_squared(int x) {
  return x * x * x * x * x;
}

int main() {
  fast_io();

  string s;
  cin >> s;
  int ans = 0;
  for (int i = 0; i < 5; i++) ans += five_squared(s[i] - '0');
  cout << ans << '\n';
}
