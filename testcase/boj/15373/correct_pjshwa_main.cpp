#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 4e5;
int lp[MAX + 1];
int a[MAX + 1];
vector<int> pr;

int main() {
  fast_io();

  for (int i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j=0; j<(int)pr.size() && pr[j]<=lp[i] && i*pr[j]<=MAX; ++j)
      lp[i * pr[j]] = pr[j];
  }

  // (n!)^2 always divides (2n)!
  // Check if (n!)^2 divides (2n-1)!
  // Check if (n!)^2 divides (2n-2)!
  // Check if (n!)^2 divides (2n-3)!
  // ...

  for (int n = 2; n <= MAX / 2; n++) {
    a[n] = 2 * n;

    for (int j = 1; j <= 10; ++j) {
      unordered_map<int, int> t;
      for (int k = 0; k < j; k++) {
        int l = 2 * n - k;
        while (l > 1) {
          t[lp[l]]--;
          l /= lp[l];
        }
      }

      for (auto [k, v] : t) {
        ll p = k;
        while (1) {
          if (n / p == 0) break;
          t[k] -= 2 * (n / p);
          p *= k;
        }
      }

      for (auto [k, v] : t) {
        ll p = k, d = 2 * n;
        while (1) {
          if (d / p == 0) break;
          t[k] += (d / p);
          p *= k;
        }
      }

      bool able = true;
      for (auto [k, v] : t) able &= (v >= 0);
      if (able) a[n] = 2 * n - j;
      else break;
    }
  }

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    if (n == 1) cout << "1\n";
    else cout << a[n] << '\n';
  }
}
