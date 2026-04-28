#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int c[MAX], a[MAX], b[MAX];

int main() {
  fast_io();

  int n;
  ll s = 0;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> c[i];
  for (int i = 0; i < n - 1; i++) cin >> a[i];
  for (int i = 0; i < n - 1; i++) cin >> b[i], s += b[i];

  ll ans = s + c[0];
  int mi = 1;
  for (int i = 0; i < n - 1; i++) {
    s += (a[i] - b[i]);
    if (ans > s + c[i + 1]) {
      ans = s + c[i + 1];
      mi = i + 2;
    }
  }
  cout << mi << ' ' << ans << '\n';
}
