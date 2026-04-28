#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;
  vector<int> factors;
  for (int i = 1; i * i <= n; i++) {
    if (n % i == 0) {
      factors.push_back(i);
      if (i * i != n) factors.push_back(n / i);
    }
  }
  sort(factors.begin(), factors.end());

  vector<set<int>> f2a(factors.size());
  f2a[0].insert(0);

  for (int i = 1; i < factors.size(); i++) for (int j = 0; j < i; j++) {
    int fi = factors[i], fj = factors[j];
    if (fi % fj) continue;

    for (int z : f2a[j]) f2a[i].insert(z - 1 + fi / fj);
  }

  cout << f2a[factors.size() - 1].size() << '\n';
  for (int x : f2a[factors.size() - 1]) cout << x << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
