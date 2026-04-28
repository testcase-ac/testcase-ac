#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n;
  cin >> n;
  vector<double> a(n);
  for (int i = 0; i < n; ++i) cin >> a[i];

  long double ans = accumulate(a.begin(), a.end(), 0.0);
  for (int i = 0; i < n - 1; ++i) ans += (a[i] * (1 - a[i + 1]) + a[i + 1] * (1 - a[i]));

  cout << fixed << setprecision(10) << ans << endl;  
}
