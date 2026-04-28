#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1.5e4;
int a[MAX];

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);

  int lp = 0, rp = n - 1;
  int ans = 0;
  while (lp < rp) {
    if (a[lp] + a[rp] > m) rp--;
    else if (a[lp] + a[rp] < m) lp++;
    else {
      ans++;
      lp++;
      rp--;
    }
  }

  cout << ans;
}
