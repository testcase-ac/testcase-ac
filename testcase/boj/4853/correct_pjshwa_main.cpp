#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int N;
void solve() {
  double ans = 1;
  for (int i = 1; i <= N / 2; ++i) {
    if (i < N / 2) ans *= (2 * i);
    ans /= (2 * i - 1);
  }
  cout << fixed << setprecision(5) << ans << '\n';
}

int main() {
  fast_io();

  while (cin >> N) solve();
}
