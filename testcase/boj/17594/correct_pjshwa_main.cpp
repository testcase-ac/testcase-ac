#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6 + 1;
ll pff[MAX], pfb[MAX];
int main() {
  fast_io();

  int n, s;
  cin >> n;

  for (int i = 1; i <= n; i++) cin >> pff[i], pfb[i] = pff[i];
  for (int i = 1; i <= n; i++) pff[i] += pff[i - 1];
  for (int i = n; i >= 1; i--) pfb[i - 1] += pfb[i];

  double ans = 0;
  for (int i = 1; i <= n; i++) ans = max(ans, (double)pff[i] / i);
  for (int i = n; i >= 1; i--) ans = max(ans, (double)pfb[i] / (n - i + 1));
  cout << fixed << setprecision(12) << ans;
}
