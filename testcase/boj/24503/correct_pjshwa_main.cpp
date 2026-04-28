#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll k, q;
  cin >> k >> q;

  ll ok = k;
  map<ll, int> m;
  for (ll i = 2; i * i <= k; i++) {
    while (ok % i == 0) {
      ok /= i;
      m[i]++;
    }
  }
  if (ok > 1) m[ok]++;

  ll left = 1, right = k + 1;
  while (left < right) {
    ll mid = (left + right) / 2;

    bool able = true;
    for (auto& [k, v] : m) {
      __int128_t cnt = 0, p = k;
      while (p <= mid) {
        cnt += mid / p;
        p *= k;
      }
      if (cnt < v) {
        able = false;
        break;
      }
    }

    if (able) right = mid;
    else left = mid + 1;
  }

  ll e = left;
  while (q--) {
    ll x;
    cin >> x;

    ll left = 1, right = e + 1;
    while (left < right) {
      ll mid = (left + right) / 2;

      bool able = true;
      ll ox = x;
      for (auto& [k, v] : m) {
        __int128_t cnt = 0, p = k;
        while (p <= mid) {
          cnt += mid / p;
          p *= k;
        }
        while (ox % k == 0) {
          ox /= k;
          cnt++;
        }
        if (cnt < v) {
          able = false;
          break;
        }
      }

      if (able) right = mid;
      else left = mid + 1;
    }

    cout << left << ' ';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
