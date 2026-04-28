#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n, w, k, ans = 0;
vector<int> f, choice;

void dfs(int cnt) {
  if (cnt == 0) {
    int ipos = w, jpos = -1;

    vector<int> cf = f;
    vector<int> deduct(n, 0);
    for (int c : choice) {
      int npos = ipos + c;
      if (npos < 0 || npos >= n) return;
      ipos = npos;

      for (int i = 0; i < cf.size(); i++) {
        if (i == jpos) deduct[i] = 0;
        else {
          deduct[i] = 3;
          if (i > 0 && cf[i - 1] > 0) deduct[i]--;
          if (i < n - 1 && cf[i + 1] > 0) deduct[i]--;
        }
      }

      int on = 0;
      for (int i = 0; i < cf.size(); i++) {
        cf[i] -= deduct[i];
        if (cf[i] > 0) on++;
      }

      if (on < k) return;
      jpos = ipos;
    }

    for (int i = 0; i < cf.size(); i++) {
      if (i == jpos) deduct[i] = 0;
      else {
        deduct[i] = 3;
        if (i > 0 && cf[i - 1] > 0) deduct[i]--;
        if (i < n - 1 && cf[i + 1] > 0) deduct[i]--;
      }
    }

    int on = 0;
    for (int i = 0; i < cf.size(); i++) {
      cf[i] -= deduct[i];
      if (cf[i] > 0) on++;
    }

    if (on >= k) ans++;
    return;
  }

  // Stay, move left or right
  for (int i : {0, -1, 1}) {
    choice.push_back(i);
    dfs(cnt - 1);
    choice.pop_back();
  }
}

void solve() {
  int t;
  cin >> n >> w >> t >> k;
  f.resize(n);
  for (int i = 0; i < n; i++) cin >> f[i];

  dfs(t - 1);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
