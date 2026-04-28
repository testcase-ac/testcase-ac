#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int a[100'000];
int main() {
  fast_io();

  int n, x;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  cin >> x;

  // Method 1
  // int tally[2'000'001];
  // memset(tally, 0, sizeof(tally));
  // for (int i = 0; i < n; i++) tally[a[i]]++;

  // long long a1 = 0;
  // for (int i = 1; i < x; i++) {
  //   int j = x - i;
  //   if (i == j) a1 += (tally[i] * tally[i] - tally[i]);
  //   else a1 += (tally[i] * tally[j]);
  // }
  // cout << a1 / 2;

  // Method 2
  // map<int, int> t;
  // for (int i = 0; i < n; i++) t[a[i]]++;

  // long long a2 = 0;
  // for (int i = 0; i < n; i++) {
  //   int lo = a[i];
  //   int hi = x - a[i];
  //   if (t.count(hi) && (lo != hi || t[hi] > 1)) a2++;
  // }
  // cout << a2 / 2;

  // Method 3
  sort(a, a + n);
  long long a3 = 0;
  int lp = 0, rp = n - 1;
  while (a[lp] < a[rp]) {
    int s = a[lp] + a[rp];
    if (s > x) rp--;
    else if (s < x) lp++;
    else {
      a3++;
      lp++;
    }
  }

  if (a[lp] == a[rp] && lp < rp) a3++;
  cout << a3;
}
