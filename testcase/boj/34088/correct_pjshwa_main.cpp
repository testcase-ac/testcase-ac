#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e4;
int A[MAXN];

void solve1() {
  cout << "1\n";
}

void solve2() {
  int diff = abs(A[0] - A[1]);
  cout << 1 + (diff != 1) << '\n';
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  if (N == 1) return solve1();
  if (N == 2) return solve2();

  mt19937 rng(0x14004);
  auto randint = [&rng](int lb, int ub) {
    return uniform_int_distribution<int>(lb, ub)(rng);
  };

  int ans = 0;
  vector<int> factors;
  unordered_map<int, int> tal;
  for (int it = 1; it <= 100; ++it) {
    int i1 = -1, i2 = -1;
    while (i1 == i2) {
      i1 = randint(0, N - 1);
      i2 = randint(0, N - 1);
    }

    int diff = abs(A[i1] - A[i2]);
    factors.clear();
    for (int i = 1; i * i <= diff; ++i) {
      if (diff % i) continue;
      factors.push_back(i);
      factors.push_back(diff / i);
    }

    for (int d : factors) {
      if (d == 1) continue;
      tal.clear();
      for (int i = 0; i < N; ++i) ++tal[A[i] % d];
      for (auto& [_, v] : tal) ans = max(ans, v);
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
