#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, tt = 0;
  string s;
  cin >> n >> s;

  int ans = 0;
  for (int i = 0; i < n; i++) for (int j = i + 2; j < n; j++) {
    int gc = 0, hc = 0;
    for (int k = i; k <= j; k++) {
      if (s[k] == 'G') gc++;
      if (s[k] == 'H') hc++;
    }

    if (gc == 1 || hc == 1) ans++;
  }
  cout << ans << '\n';
}
