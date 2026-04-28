#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

struct W {
  int si, ei, mi;

  bool operator<(const W &b) const {
    return si < b.si;
  }
} a[50'000];

void solve() {
  int k, n, c;
  cin >> k >> n >> c;
  for (int i = 0; i < k; i++) {
    int si, ei, mi;
    cin >> si >> ei >> mi;
    a[i] = {si, ei, mi};
  }
  sort(a, a + k);

  int ans = 0, cur = 0;
  map<int, int> et;

  for (int i = 0; i < k; i++) {
    auto it = et.begin();
    while (it != et.end() && it->first <= a[i].si) {
      ans += it->second;
      cur -= it->second;
      et.erase(it++);
    }

    et[a[i].ei] += a[i].mi;
    cur += a[i].mi;
    it = et.end();
    --it;

    while (cur > c) {
      if (cur - it->second >= c) {
        cur -= it->second;
        et.erase(it--);
      }
      else {
        it->second -= cur - c;
        cur = c;
      }
    }
  }

  cout << ans + cur << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
