#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int a[200'000];
int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  ll sum = accumulate(a, a + n, 0LL);
  ll mxv = *max_element(a, a + n);
  if (sum > 2 * mxv) cout << (sum & 1);
  else cout << 2 * mxv - sum;
}
