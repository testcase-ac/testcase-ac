#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5000;
int A[MAXN];

void solve() {
  int N; cin >> N;

  int cur = N - 1, rp = N - 2, lp = 0;
  A[N - 1] = N;

  auto fill_left = [&] {
    if (lp > rp) return;
    A[lp++] = cur--;
  };
  auto fill_right = [&] {
    if (lp > rp) return;
    A[rp--] = cur--;
  };

  while (cur >= 1) {
    fill_left();
    fill_left();
    fill_right();
    fill_right();
  }

  for (int i = 0; i < N; ++i) cout << A[i] << " \n"[i == N - 1];
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
