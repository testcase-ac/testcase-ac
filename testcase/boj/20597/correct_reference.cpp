#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  // dp_m[x] is the parity of involutions on m elements with exactly x inversions.
  vector<unsigned char> prev2(k + 1), prev1(k + 1), cur(k + 1);
  prev2[0] = 1;  // m = 0
  prev1[0] = 1;  // m = 1

  if (n == 1) {
    cout << (k == 0 ? 1 : 0) << '\n';
    return 0;
  }

  for (int len = 2; len <= n; len++) {
    fill(cur.begin(), cur.end(), 0);

    vector<unsigned char> prefix_even(k + 2), prefix_odd(k + 2);
    for (int inv = 0; inv <= k; inv++) {
      prefix_even[inv + 1] = prefix_even[inv];
      prefix_odd[inv + 1] = prefix_odd[inv];
      if (inv % 2 == 0) {
        prefix_even[inv + 1] ^= prev2[inv];
      } else {
        prefix_odd[inv + 1] ^= prev2[inv];
      }
    }

    int max_delta = 2 * len - 3;
    for (int inv = 0; inv <= k; inv++) {
      unsigned char value = prev1[inv];

      int lo = max(0, inv - max_delta);
      int hi = inv - 1;
      if (lo <= hi) {
        int want_parity = 1 - (inv % 2);
        if (want_parity == 0) {
          value ^= prefix_even[hi + 1] ^ prefix_even[lo];
        } else {
          value ^= prefix_odd[hi + 1] ^ prefix_odd[lo];
        }
      }

      cur[inv] = value;
    }

    prev2.swap(prev1);
    prev1.swap(cur);
  }

  cout << int(prev1[k]) << '\n';
  return 0;
}
