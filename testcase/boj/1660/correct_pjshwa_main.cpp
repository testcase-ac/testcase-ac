#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 3e5;
int d[MAXV + 1];

void solve() {
  int N = 130;

  vector<ll> A(N + 1);
  for (ll i = 1; i <= N; i++) A[i] = i * (i - 1) / 2;
  for (ll i = 2; i <= N; i++) A[i] += A[i - 1];

  memset(d, 0x3f, sizeof(d));
  d[0] = 0;
  for (int i = 1; i <= N; i++) {
    int val = A[i];
    for (int v = val; v <= MAXV; v++) {
      d[v] = min(d[v], d[v - val] + 1);
    }
  }

  int R; cin >> R;
  cout << d[R] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
