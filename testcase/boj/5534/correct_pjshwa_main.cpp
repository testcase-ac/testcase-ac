#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool w[100];
string s, t[100];
int sz;

bool match(int pos, int d, int step) {
  bool able = true;
  for (int i = 0; i < sz; i++) {
    if (d + step * i >= t[pos].size()) {
      able = false;
      break;
    }
    able &= s[i] == t[pos][d + step * i];
  }
  return able;
}

int main() {
  fast_io();

  int n;
  cin >> n >> s;
  for (int i = 0; i < n; i++) cin >> t[i];

  sz = s.size();
  for (int step = 1; step < 100; step++) {
    for (int d = 0; d < 100; d++) {
      for (int i = 0; i < n; i++) if (match(i, d, step)) w[i] = true;
    }
  }

  int cnt = 0;
  for (int i = 0; i < n; i++) if (w[i]) cnt++;
  cout << cnt << '\n';
}
