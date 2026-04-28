#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, CMAX = 3e4;
long long a[MAX], lcnt[CMAX + 1], rcnt[CMAX + 1];
int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i], rcnt[a[i]]++;

  long long ans = 0;
  for (int i = 0; i < n; i++) {
    rcnt[a[i]]--;
    for (int c = 1; c <= CMAX; c++) {
      int rn = 2 * a[i] - c;
      if (rn <= 0 || rn > CMAX) continue;
      ans += lcnt[c] * rcnt[rn];
    }
    lcnt[a[i]]++;
  }

  cout << ans;
}
