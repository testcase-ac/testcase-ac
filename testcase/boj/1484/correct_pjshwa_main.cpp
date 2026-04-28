#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int g, a, b;
  cin >> g;

  vector<int> ans;
  for (int i = 1; i < sqrt(g); i++) {
    if (g % i == 0) {
      a = i;
      b = g / i;
      if (a % 2 == b % 2) ans.push_back((a + b) / 2);
    }
  }
  sort(ans.begin(), ans.end());

  if (ans.size()) for (int el : ans) cout << el << '\n';
  else cout << -1;
}
