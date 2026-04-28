#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n, m, k, p[10];
ll ans, cm, cstock, cloan, day;
vector<int> choice;

void full_sell() {
  cm += cstock * p[day];
  cstock = 0;
}

void full_buy() {
  if (cloan > cm) return;
  cm -= cloan;
  cloan = cm * k;
  cm += cloan;

  int nstock = cm / p[day];
  if (nstock == 0) {
    cm -= cloan;
    cloan = 0;
    return;
  }
  cstock += cm / p[day];
  cm -= cstock * p[day];
}

void dfs(int cnt) {
  if (cnt == 0) {
    cm = m, cstock = 0, cloan = 0;
    for (day = 0; day < n; day++) {
      int c = choice[day];

      if (c == 1) {
        full_sell();
        full_buy();
      }
      if (c == 2) full_sell();
      if (c == 3) full_buy();
    }

    // if (cm == 588000) {
    //   for (int i = 0; i < n; i++) {
    //     cout << choice[i] << " ";
    //   }
    //   cout << endl;
    // }
    ans = max(ans, cm);
    return;
  }

  // Do nothing / Sell & Buy / Sell only / Buy only
  for (int i : {0, 1, 2, 3}) {
    choice.push_back(i);
    dfs(cnt - 1);
    choice.pop_back();
  }
}

void solve() {
  cin >> n >> m >> k;
  for (int i = 0; i < n; i++) cin >> p[i];
  dfs(n);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
