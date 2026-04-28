#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
ull L[MAXN], R[MAXN];
int N;

bool f(ull x) {
  auto val = x;
  for (int i = 0; i < N; ++i) {
    auto l = L[i], r = R[i];
    if (l > x || r < x) continue;

    ull e = (x | l) + (x & r) * (l ^ r);
    val ^= e;
  }
  return val >= 0x0123456789abcdef;
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; ++i) cin >> L[i];
  for (int i = 0; i < N; ++i) cin >> R[i];

  ll l = 0, r = 1e18; ++r;
  while (l < r) {
    ll m = (l + r) / 2;
    if (f(m)) r = m;
    else l = m + 1;
  }
  cout << l - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
