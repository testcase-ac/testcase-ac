#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5, INF = 1e9 + 7;
int a[MAX];

int main() {
  fast_io();

  int n, l;
  cin >> n >> l;
  for (int i = 0; i < n; i++) cin >> a[i];

  ll psum = a[n - 1];
  for (int i = n - 2; i >= 0; i--) {
    if (psum <= (ll)(n - 1 - i) * (a[i] - l)) return cout << "unstable\n", 0;
    if (psum >= (ll)(n - 1 - i) * (a[i] + l)) return cout << "unstable\n", 0;
    psum += a[i];
  }

  cout << "stable\n";
}
