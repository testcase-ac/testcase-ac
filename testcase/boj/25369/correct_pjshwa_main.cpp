#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n, opp = 1;
vector<int> cur;
int curm = 1;

void dfs(int i) {
  if (i == n) {
    if (curm > opp) {
      for (int e : cur) cout << e << ' ';
      cout << '\n';
      exit(0);
    }
    return;
  }

  for (int k = 1; k <= 9; k++) {
    curm *= k;
    cur.push_back(k);
    dfs(i + 1);
    cur.pop_back();
    curm /= k;
  }
}

void solve() {
  cin >> n;
  for (int i = 0, x; i < n; i++) {
    cin >> x;
    opp *= x;
  }
  dfs(0);
  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
