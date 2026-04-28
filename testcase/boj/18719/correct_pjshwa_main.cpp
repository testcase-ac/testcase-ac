#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1 << 20;
ll t[MAX], F[MAX];

void solve() {
  int n;
  cin >> n;

  memset(t, 0, sizeof(t));
  vector<int> A(n);
  for (int i = 0; i < n; i++) {
    cin >> A[i];
    t[A[i]]++;
  }

  for (int i = 0; i < (1 << 20); i++) F[i] = t[i];

  for (int i = 0; i < 20; i++) for (int x = 0; x < (1 << 20); x++) {
    if (x & (1 << i)) F[x] += F[x ^ (1 << i)];
  }

  ll ans = 0;
  for (int i = 0; i < n; i++) ans += F[A[i]];
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
