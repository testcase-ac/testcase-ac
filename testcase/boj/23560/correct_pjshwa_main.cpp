#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

deque<int> current;
int n, t;
int ans = 0;

void dfs(int di, int ti) {
  if (di == n) return ans++, void();

  if (ti == 0) {
    if (current.front() == 1) {
      current.pop_front();
      dfs(di, ti + 1);
      current.push_front(1);
    }
    if (current.size() > 1 && current.back() == 1) {
      current.pop_back();
      dfs(di, ti + 1);
      current.push_back(1);
    }
  }
  if (ti == 1) {
    if (current.front() == 2) {
      current.pop_front();
      dfs(di, ti + 1);
      current.push_front(2);
    }
    if (current.size() > 1 && current.back() == 2) {
      current.pop_back();
      dfs(di, ti + 1);
      current.push_back(2);
    }
  }
  if (ti == 2) {
    if (current.front() == 1) {
      current.pop_front();
      dfs(di + 1, 0);
      current.push_front(1);
    }
    if (current.size() > 1 && current.back() == 1) {
      current.pop_back();
      dfs(di + 1, 0);
      current.push_back(1);
    }
  }
}

void solve() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    current.push_back(1);
    current.push_back(2);
    current.push_back(1);
  }

  dfs(0, 0);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
