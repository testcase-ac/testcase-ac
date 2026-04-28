#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;
  map<int, int> p;
  for (int i = 2; i * i <= n; i++) {
    while (n % i == 0) {
      n /= i;
      p[i]++;
    }
  }
  if (n > 1) p[n]++;

  int left = 1, right = 1e8 + 1;
  while (left < right) {
    int mid = (left + right) / 2;

    bool able = true;
    for (auto [k, v] : p) {
      ll pt = k, cnt = 0;
      while (pt <= mid) {
        cnt += mid / pt;
        pt *= k;
      }
      if (cnt < v) {
        able = false;
        break;
      }
    }

    if (able) right = mid;
    else left = mid + 1;
  }

  cout << left << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
