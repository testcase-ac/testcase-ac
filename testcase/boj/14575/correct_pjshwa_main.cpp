#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, INF = 1e9 + 7;
pii pl[MAX];

void solve() {
  int n, t;
  cin >> n >> t;

  int lsum = 0, rsum = 0;
  int left = 0;
  for (int i = 0; i < n; i++) {
    cin >> pl[i].first >> pl[i].second;
    lsum += pl[i].first;
    rsum += pl[i].second;
    left = max(left, pl[i].first);
  }

  if (t < lsum || t > rsum) return cout << "-1\n", void();

  int right = INF;
  while (left < right) {
    int mid = (left + right) / 2;
    int csum = 0;
    for (int i = 0; i < n; i++) csum += min(mid, pl[i].second);

    if (csum < t) left = mid + 1;
    else right = mid;
  }

  cout << left << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
