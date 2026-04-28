#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int L[MAX + 1];

void solve() {
  int M, N;
  cin >> M >> N;
  for (int i = 1; i <= N; i++) cin >> L[i];

  int left = 1, right = 1e9 + 1;
  while (left < right) {
    int mid = (left + right) / 2;
    ll cnt = 0;
    for (int i = 1; i <= N; i++) cnt += L[i] / mid;

    if (cnt >= M) left = mid + 1;
    else right = mid;
  }

  cout << left - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
