#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
ll w[MAX + 1], d[MAX + 1];
int n;

ll max_work(int diff) {
  memset(d, 0, sizeof(d));
  for (int i = 1; i <= n; i++) {
    d[i] = max(w[i], d[i - 1]);
    if (i - diff - 1 >= 1) d[i] = max(d[i], d[i - diff - 1] + w[i]);
  }
  return d[n];
}

void solve() {
  ll m;
  cin >> n >> m;

  ll sum = 0;
  for (int i = 1; i <= n; i++) {
    cin >> w[i];
    sum += w[i];
    if (w[i] >= m) return cout << "Free!" << '\n', void();
  }
  if (sum < m) return cout << "-1\n", void();

  int left = 1, right = n + 10;
  while (left < right) {
    int mid = (left + right) / 2;

    if (max_work(mid) >= m) left = mid + 1;
    else right = mid;
  }

  cout << left - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
