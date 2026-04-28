#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXL = 20, LIM = 1e12;
vector<ll> lucky_numbers[MAXL + 1], Lv;

void solve() {
  ll L, R; cin >> L >> R;
  cout << upper_bound(Lv.begin(), Lv.end(), R) - lower_bound(Lv.begin(), Lv.end(), L) << '\n';
}

int main() {
  fast_io();

  for (int d = 1; d <= 12; ++d) {
    for (int s = 0; s < (1 << d); ++s) {
      ll x = 0;
      for (int i = 0; i < d; ++i) {
        x = x * 10 + (s & (1 << i) ? 7 : 4);
      }
      if (x <= LIM) lucky_numbers[1].push_back(x);
    }
  }
  sort(lucky_numbers[1].begin(), lucky_numbers[1].end());
  for (int l = 2; l <= MAXL; ++l) {
    for (ll l1 : lucky_numbers[l - 1]) for (ll l2 : lucky_numbers[1]) {
      if (l1 * l2 > LIM) break;
      lucky_numbers[l].push_back(l1 * l2);
    }
    sort(lucky_numbers[l].begin(), lucky_numbers[l].end());
    lucky_numbers[l].erase(
      unique(lucky_numbers[l].begin(), lucky_numbers[l].end()), lucky_numbers[l].end()
    );
  }

  for (int i = 1; i <= MAXL; ++i) {
    for (ll x : lucky_numbers[i]) Lv.push_back(x);
  }
  sort(Lv.begin(), Lv.end());
  Lv.erase(unique(Lv.begin(), Lv.end()), Lv.end());

  int t = 1;
  cin >> t;
  while (t--) solve();
}
