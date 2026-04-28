#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
map<int, bool> vis;
set<int> marked;

void solve() {
  int n, k;
  cin >> n >> k;

  vector<int> spots(n);
  queue<int> next;
  for (int i = 0; i < n; i++) {
    cin >> spots[i];
    vis[spots[i]] = 1;
  }
  for (int i = 0; i < n; i++) {
    if (!vis[spots[i] - 1]) {
      next.push(spots[i] - 1);
      vis[spots[i] - 1] = 1;
    }
    if (!vis[spots[i] + 1]) {
      next.push(spots[i] + 1);
      vis[spots[i] + 1] = 1;
    }
  }
  sort(spots.begin(), spots.end());

  int cnt = 0;
  while (cnt < k) {
    int f = next.front();
    next.pop();

    cnt++;
    marked.insert(f);

    if (!vis[f + 1]) {
      vis[f + 1] = 1;
      next.push(f + 1);
    }
    if (!vis[f - 1]) {
      vis[f - 1] = 1;
      next.push(f - 1);
    }
  }

  ll ans = 0;
  for (ll mark : marked) {
    auto it = lower_bound(spots.begin(), spots.end(), mark);

    ll dist = 1e18;
    if (it != spots.begin()) {
      dist = min(dist, abs(mark - *(it - 1)));
    }
    if (it != spots.end()) {
      dist = min(dist, abs(mark - *it));
    }
    ans += dist;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
