#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int a[MAX + 1], p[MAX + 1];
int N, S, W, Q;

void solve_Q2() {
  ll ans = 0, acc = 0;
  for (int i = N - 1; i >= 0; i--) {
    if (a[i] % 2 == 0) acc++;
    if (a[i]) ans += acc;
  }
  cout << ans << '\n';
}

void solve_Q5() {
  ll ans = 0, acc = 0;
  for (int i = N - 1; i >= 0; i--) {
    if (a[i] % 5 == 0) acc++;
    if (a[i]) ans += acc;
  }
  cout << ans << '\n';
}

void solve() {
  int g = S;
  for (int i = 0; i < N; i++) {
    a[i] = (g / 7) % 10;
    if (g % 2 == 0) g = (g / 2);
    else g = (g / 2) ^ W;
  }

  if (Q == 2) return solve_Q2();
  if (Q == 5) return solve_Q5();

  map<int, int> t;
  t[0] = 1;
  p[N] = 0;

  ll ans = 0, m = 1;
  for (int i = N - 1; i >= 0; i--) {
    p[i] = (p[i + 1] + a[i] * m) % Q;
    m = (m * 10) % Q;
    if (a[i]) ans += t[p[i]];
    t[p[i]]++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> N >> S >> W >> Q;
    if (N == 0) break;
    solve();
  }
}
