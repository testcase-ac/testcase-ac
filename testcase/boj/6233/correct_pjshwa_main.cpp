#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5000;
int b[MAX], c[MAX + 1];

int main() {
  fast_io();

  int n;
  cin >> n;
  
  char cur = 'F';
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    if (s[0] != cur) {
      cur = s[0];
      b[i] = 1;
    }
  }

  int mink = -1, minf = 1e9;
  for (int k = 1; k <= n; k++) {
    for (int i = 0; i < n; ++i) c[i] = b[i];

    int fcount = 0;
    for (int i = 0; i <= n - k; ++i) {
      if (c[i]) fcount++;
      c[i + k] ^= c[i];
    }

    bool able = true;
    for (int i = n - k + 1; i < n; ++i) able &= !c[i];

    if (able && fcount < minf) {
      minf = fcount;
      mink = k;
    }
  }

  cout << mink << ' ' << minf << '\n';
}
