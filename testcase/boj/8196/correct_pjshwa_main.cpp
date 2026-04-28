#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void compress(vector<int>& a) {
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
}

const int MAX = 1e6;
ll d[MAX + 1][2];

void solve() {
  int n; cin >> n;
  vector<int> A(n);
  for (int& x : A) cin >> x;
  compress(A); n = A.size();

  for (int i = 1; i <= n; i++) {
    int val = A[i - 1];
    d[i][0] = max(d[i - 1][1] + val, d[i - 1][0]);
    d[i][1] = min(d[i - 1][0] - val, d[i - 1][1]);
  }
  cout << d[n][0] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
