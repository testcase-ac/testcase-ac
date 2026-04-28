#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX = 1e5 + 1;
int values[MAX];
int main() {
  int n;
  cin >> n;

  for (int i = 0; i < n; i++) cin >> values[i];
  int lp = 0, rp = n - 1, mnv, mxv, cv, msum = 2e9 + 1;

  while (lp < rp) {
    cv = values[lp] + values[rp];
    if (msum > abs(cv)) {
      msum = abs(cv);
      mnv = values[lp];
      mxv = values[rp];
    }

    if (cv < 0) lp++;
    else rp--;
  }

  cout << mnv << ' ' << mxv << '\n';
}
