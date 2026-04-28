#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int a[MAX + 1], t[MAX + 1], c[MAX + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    t[a[i]]++;
  }

  for (int i = 1; i <= MAX; i++) {
    for (int j = i; j <= MAX; j += i) c[j] += t[i];
  }

  for (int i = 0; i < n; i++) cout << c[a[i]] - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
