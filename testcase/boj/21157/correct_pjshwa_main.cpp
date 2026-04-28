#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int Ysch[MAXN + 1];

void solve() {
  int s, n; cin >> s >> n;
  vector<int> wait, ys;
  for (int i = 0; i < n; ++i) {
    int d; string t; cin >> d >> t;
    if (t == "y" && d <= n) ys.push_back(d);
    else wait.push_back(d);
  }
  sort(ys.begin(), ys.end());
  sort(wait.begin(), wait.end(), greater<int>());

  int t = n;
  while (!ys.empty()) {
    int y = ys.back(); ys.pop_back();
    while (t > y) --t;
    if (t == 0) return cout << "No\n", void();
    Ysch[t--] = y;
  }

  for (int t = 1; t <= n; ++t) {
    int cnt = Ysch[t] > 0;
    while (!wait.empty() && cnt < s) {
      int d = wait.back(); wait.pop_back();
      if (d < t) return cout << "No\n", void();
      ++cnt;
    }
  }

  assert(wait.empty());
  cout << "Yes\n";
}

int main() {
  // fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
