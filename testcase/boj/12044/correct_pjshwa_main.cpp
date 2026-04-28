#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int tc, t[MAX];

void solve() {
  cout << "Case #" << ++tc << ": ";

  int n, k;
  cin >> n >> k;

  map<int, int> A, B;

  for (int j = 0; j < n; j++) cin >> t[j];
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    for (int j = 0; j < n; j++) A[x ^ t[j]]++;
  }

  for (int j = 0; j < n; j++) cin >> t[j];
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    for (int j = 0; j < n; j++) B[x ^ t[j]]++;
  }

  ll ans = 0;
  for (auto& [v, c] : A) {
    if (B.count(v ^ k)) ans += (ll)c * B[v ^ k];
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
