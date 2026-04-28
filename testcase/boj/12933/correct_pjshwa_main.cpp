#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int w[4];
int main() {
  fast_io();

  int mducks = 0, cducks = 0;
  string s;
  cin >> s;
  for (char c : s) {
    if (c == 'q') {
      w[0]++;
      cducks++;
    }
    if (c == 'u') {
      if (w[0] == 0) return cout << -1, 0;
      w[0]--;
      w[1]++;
    }
    if (c == 'a') {
      if (w[1] == 0) return cout << -1, 0;
      w[1]--;
      w[2]++;
    }
    if (c == 'c') {
      if (w[2] == 0) return cout << -1, 0;
      w[2]--;
      w[3]++;
    }
    if (c == 'k') {
      if (w[3] == 0) return cout << -1, 0;
      w[3]--;
      cducks--;
    }

    mducks = max(mducks, cducks);
  }

  if (w[0] == 0 && w[1] == 0 && w[2] == 0 && w[3] == 0) cout << mducks;
  else cout << -1;
}
