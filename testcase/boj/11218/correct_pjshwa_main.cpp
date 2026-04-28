#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 30;
int A[MAX + 1], U[MAX + 1];
double H[MAX + 1], W[MAX + 1];

bool r(int i, int need) {
  if (i > MAX) return false;

  int v = min(need, A[i]);
  need -= v; U[i] = v;
  if (need) return r(i + 1, need * 2);
  else return true;
}

void solve() {
  int n; cin >> n;
  for (int i = 2; i <= n; i++) cin >> A[i];

  H[2] = 0.4204482076268572, W[2] = 0.5946035575013605;
  for (int i = 3; i <= n; i++) {
    H[i] = max(H[i - 1], W[i - 1]) / 2;
    W[i] = min(H[i - 1], W[i - 1]);
  }

  if (r(1, 1)) {
    double ans = 0;
    for (int i = n; i >= 2; i--) {
      assert(U[i] % 2 == 0);

      int h = U[i] / 2;
      ans += h * max(H[i], W[i]);
      U[i - 1] += h;
    }
    cout << fixed << setprecision(10) << ans << '\n';
  }
  else cout << "impossible\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
