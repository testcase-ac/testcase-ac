#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX = 5e3 + 1;
ll values[MAX];
int main() {
  int n;
  cin >> n;

  for (int i = 0; i < n; i++) cin >> values[i];
  sort(values, values + n);

  ll mnv, mmv, mxv, cv, msum = 3e9 + 1;
  for (int i = 1; i < n - 1; i++) {
    int lp = 0, rp = n - 1;

    while (lp < i && i < rp) {
      cv = values[lp] + values[i] + values[rp];
      if (msum > abs(cv)) {
        msum = abs(cv);
        mnv = values[lp];
        mmv = values[i];
        mxv = values[rp];
      }

      if (cv < 0) lp++;
      else rp--;
    }
  }

  cout << mnv << ' ' << mmv << ' ' << mxv << '\n';
}
