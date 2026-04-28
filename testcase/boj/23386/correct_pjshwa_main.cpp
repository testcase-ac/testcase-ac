#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int rsum[MAX + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
    int x;
    cin >> x;
    rsum[i] += x;
  }
  sort(rsum + 1, rsum + n + 1);

  ll s1 = accumulate(rsum + 1, rsum + n / 2 + 1, 0LL);
  ll s2 = accumulate(rsum + n / 2 + 1, rsum + n + 1, 0LL);
  cout << (s2 - s1) / 2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
