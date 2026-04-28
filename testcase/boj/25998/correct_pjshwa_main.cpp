#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
int w[MAX];

void solve() {
  int n, k, ans = 0; cin >> n >> k;
  for (int i = 0; i < n; ++i) {
    cin >> w[i];

    int add = max((w[i] + k - 1) / k, 0);
    ans += add; w[i] %= k;
  }

  
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
