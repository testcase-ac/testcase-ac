#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 10000;
int a[MAX];
bool vis[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  queue<int> z, oz, tz;
  for (int i = 0; i < n; i++) {
    if (a[i] % 3 == 0) z.push(i);
    if (a[i] % 3 == 1) oz.push(i);
    if (a[i] % 3 == 2) tz.push(i);
  }

  vector<int> ans;
  while (!z.empty() || !oz.empty() || !tz.empty()) {
    if (!z.empty()) {
      ans.push_back(a[z.front()]);
      z.pop();
    }
    if (!oz.empty()) {
      ans.push_back(a[oz.front()]);
      oz.pop();
    }
    else if (!tz.empty()) {
      ans.push_back(a[tz.front()]);
      tz.pop();
    }
  }

  for (int i = 0; i < n; i++) {
    if (i < n - 1 && ans[i] % 3 == 1 && ans[i + 1] % 3 == 2) {
      for (int j = 0; j < i; j++) swap(ans[j], ans[j + 1]);
      break;
    }
  }

  for (int i = 0; i < n; i++) {
    if (i < n - 1 && (ans[i] + ans[i + 1]) % 3 == 0) return cout << "-1\n", void();
  }

  for (int i = 0; i < n; i++) cout << ans[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
