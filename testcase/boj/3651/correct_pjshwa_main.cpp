#include <bits/stdc++.h>
#define ll long long
#define pll pair<ll, ll>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  ll m, n, k, left, right, mid, mult_v;
  cin >> m;

  set<pll> ans;

  // Step 1. Find cases where k = 1 (simple)
  ans.insert({m, 1});
  ans.insert({m, m - 1});

  // Step 2. Find cases where k = 2 (2k = n(n - 1) where n is some natural number)
  // Find by binary search as n could be upto about 10^8
  left = 1;
  right = 1e9;
  mid = (left + right) / 2;
  while (left < right) {
    if (mid * mid - mid == 2 * m) break;
    else if (mid * mid - mid < 2 * m) left = mid + 1;
    else right = mid;

    mid = (left + right) / 2;
  }

  if (mid * mid - mid == 2 * m) {
    ans.insert({mid, 2});
    ans.insert({mid, mid - 2});
  }

  // Step 3. Find cases where k >= 3
  // k cannot be larger than some small number as m is limited (<= 10^15)
  // Brute force search
  k = 3;
  bool first_overflow;
  while (1) {
    n = 2 * k;
    first_overflow = true;
    while (1) {
      mult_v = 1;
      for (int i = 0; i < k; i++) {
        mult_v *= (n - i);
        mult_v /= (i + 1);
      }

      if (mult_v == m) {
        ans.insert({n, k});
        ans.insert({n, n - k});
        first_overflow = false;
        break;
      }
      else if (mult_v > m) break;
      else if (mult_v < m) first_overflow = false;

      n++;
    }

    if (first_overflow) break;
    k++;
  }

  // Print answers to stdout
  cout << ans.size() << '\n';
  for (auto &x : ans) {
    tie(n, k) = x;
    cout << n << ' ' << k << '\n';
  }
}
