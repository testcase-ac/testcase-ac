#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int A[MAX + 1];

void solve() {
  int n, b, a;
  cin >> n >> b >> a;
  for (int i = 1; i <= n; i++) cin >> A[i];
  sort(A + 1, A + n + 1);

  ll acc = 0;
  for (int i = 1; i <= n; i++) {
    acc += A[i] / 2;
    if (i > a) acc += A[i - a] / 2;

    if (acc > b) return cout << i - 1 << '\n', void();
  }
  cout << n << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
