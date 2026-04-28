#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3e5;
ll A[MAX + 1], B[MAX + 1], C[MAX + 1], D[MAX + 1], E[MAX + 1];
int N;

ll f(ll o) {
  ll t = E[0] + o;
  for (int i = 1; i <= N; i++) {
    if (t < C[i]) t = C[i];

    ll X = (t - C[i]) / A[i];
    if (t + D[i] > C[i] + A[i] * X + B[i]) {
      t = C[i] + A[i] * (X + 1);
    }
    t += D[i];
    t += E[i];
  }
  return t;
}

void solve() {
  int T;
  cin >> N >> T;
  for (int i = 1; i <= N; i++) cin >> A[i] >> B[i] >> C[i] >> D[i];
  for (int i = 0; i <= N; i++) cin >> E[i];

  int left = 0, right = T + 1;
  while (left < right) {
    int mid = (left + right) / 2;
    if (f(mid) < T) left = mid + 1;
    else right = mid;
  }

  if (f(left) == T) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
