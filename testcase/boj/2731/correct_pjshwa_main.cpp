#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n;
ll s, cnum, cmod = 1;

bool compare(int i) {
  ll num = (cmod / 10) * i + cnum;
  __int128_t id = 1;
  for (int j = 0; j < 3; j++) id = (id * num) % cmod;
  return id == s % cmod;
}

void dfs(int step) {
  if (step == n) {
    cout << cnum << '\n';
    return;
  }

  cmod *= 10;
  for (int i = 0; i < 10; i++) {
    if (compare(i)) {
      cnum += (cmod / 10) * i;
      dfs(step + 1);
      cnum -= (cmod / 10) * i;
    }
  }
  cmod /= 10;
}

void solve() {
  cin >> s;
  n = to_string(s).size();
  dfs(0);
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
