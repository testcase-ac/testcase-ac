#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5e5;
int A[MAX];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];

  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  auto randint = [&rng](int lb, int ub) {
    return uniform_int_distribution<int>(lb, ub)(rng);
  };

  int it = 10;
  while (it--) {
    int i = randint(0, N - 1);
    int val = A[i];

    unordered_map<int, int> map_g;
    for (int j = 0; j < N; j++) {
      int g = __gcd(val, A[j]);
      map_g[g]++;
    }

    // Upper bound 1344
    vector<int> facts;
    for (int f = 1; f * f <= val; f++) {
      if (val % f) continue;
      facts.push_back(f);
      if (f * f != val) facts.push_back(val / f);
    }

    for (int f : facts) {
      if (f == 1) continue;

      int c = 0;
      for (auto& [k, v] : map_g) if (k % f == 0) c += v;

      if (c >= (N + 1) / 2) {
        cout << "YES\n";
        int z = 0;
        for (int j = 0; j < N; j++) {
          if (A[j] % f == 0) cout << A[j] << ' ', z++;
          if (z == (N + 1) / 2) return;
        }
      }
    }
  }

  cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
