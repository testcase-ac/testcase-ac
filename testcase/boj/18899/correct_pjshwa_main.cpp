#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

__int128_t pw11[30], pw2[30];
vector<int> run;

void dfs(int p, int b, ll cur) {
  if (b == -1) {
    if (cur == 0) {
      for (int d : run) cout << d;
      cout << '\n';
      exit(0);
    }
    return;
  }

  int cnt = 0;
  for (int c = 9; c >= (p ? 0 : 1); c--) {
    __int128_t val = c * pw11[b] * pw2[p];
    if (val <= cur) {
      cnt++;
      run.push_back(c);
      dfs(p + 1, b - 1, cur - val);
      run.pop_back();
    }
    if (cnt == 2) return;
  }
}

void solve() {
  ll n;
  cin >> n;

  for (int w = 1; w <= 19; w++) {
    dfs(0, w - 1, n);
  }

  cout << "NIE\n";
}

int main() {
  fast_io();

  pw11[0] = pw2[0] = 1;
  for (int i = 1; i < 30; i++) pw11[i] = pw11[i - 1] * 11;
  for (int i = 1; i < 30; i++) pw2[i] = pw2[i - 1] * 2;

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
