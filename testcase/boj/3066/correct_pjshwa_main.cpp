#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, next;
  cin >> n;

  vector<int> lis_vector;
  lis_vector.push_back(-(1e9 + 1));

  for (int i = 0; i < n; i++) {
    cin >> next;

    if (next > lis_vector.back()) lis_vector.push_back(next);
    else {
      auto it = upper_bound(lis_vector.begin(), lis_vector.end(), next - 1);
      *it = next;
    }
  }

  cout << lis_vector.size() - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
