#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX = 1e6;
ll a[MAX];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    reverse(s.begin(), s.end());
    a[i] = stoll(s);
  }

  sort(a, a + n);
  for (int i = 0; i < n; i++) {
    cout << a[i] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
