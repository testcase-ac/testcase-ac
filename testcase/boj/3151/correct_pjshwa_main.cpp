#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int a[(int)1e4];
int main() {
  fast_io();

  int n, lp, rp, target, s, lcnt, rcnt;
  ll cnt = 0;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);

  for (int i = 1; i < n - 1; i++) {
    lp = 0;
    rp = n - 1;
    target = -a[i];

    while (lp < i && i < rp) {
      s = a[lp] + a[rp];
      if (s < target) lp++;
      else if (s > target) rp--;
      else {
        lcnt = 1;
        rcnt = 1;
        while (i + 1 < rp && a[rp] == a[rp - 1]) {
          rcnt++;
          rp--;
        }
        while (lp < i - 1 && a[lp] == a[lp + 1]) {
          lcnt++;
          lp++;
        }
        rp--;
        lp++;
        cnt += (lcnt * rcnt);
      }
    }
  }

  cout << cnt << '\n';
}
