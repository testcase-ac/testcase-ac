#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

pii a[1'000'000];
int main() {
  fast_io();

  int n, as, ae;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
  sort(a, a + n);

  int s = 0, cs = -2e9, ce = -2e9;
  for (int i = 0; i < n; i++) {
    tie(as, ae) = a[i];
    if (ce < as) {
      s += (ce - cs);
      cs = as;
      ce = ae;
    }
    else ce = max(ae, ce);
  }

  cout << s + ce - cs;
}
