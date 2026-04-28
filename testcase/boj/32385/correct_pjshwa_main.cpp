#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 1e9;
int N;

void solve_odd() {
  ll sum = N;
  cout << N << ' ';
  for (int i = 1; i <= N / 2; ++i) {
    int a = -MAXV + i, b = MAXV - i;
    cout << a << ' ' << b << ' ';
  }
  assert(sum % N == 0);
  cout << sum / N << '\n';
}

void solve_even() {
  ll sum = 0;
  for (int i = 1; i <= N / 2; ++i) {
    int a = i, b = MAXV - i;
    cout << a << ' ' << b << ' ';
    sum += a + b;
  }
  assert(sum % N == 0);
  cout << sum / N << '\n';
}

void solve() {
  cin >> N;
  if (N & 1) solve_odd();
  else solve_even();
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
