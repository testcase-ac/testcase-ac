#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int a[50000], n;

int do_search(int x) {
  int rp = n - 1, cnt = 0;
  for (int lp = 0; lp < rp; lp++) {
    while (lp < rp && a[lp] + a[rp] > x) rp--;
    cnt += (rp - lp);
  }
  return cnt;
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);

  int Sx = ceil(1.0 * n * (n - 1) / 4);
  ll left = 2, right = 2e9;
  ll mid = (left + right) / 2;

  while (left < right) {
    if (do_search(mid) < Sx) left = mid + 1;
    else right = mid;

    mid = (left + right) / 2;
  }
  cout << mid;
}
