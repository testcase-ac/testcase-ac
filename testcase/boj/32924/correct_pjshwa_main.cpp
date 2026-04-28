#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int A[MAXN], B[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];

  vector<pii> U;
  for (int i = 0; i < N; ++i) {
    cin >> B[i];
    U.emplace_back(B[i] - A[i], A[i]);
  }
  sort(U.begin(), U.end(), greater<pii>());

  for (int i = 0; i < N; ++i) {
    if (U[i].first < 0) return cout << "-1\n", void();
    if (i == 0) continue;

    auto [d1, a1] = U[i - 1];
    auto [d2, a2] = U[i];
    if (d1 != d2 && a1 < a2) return cout << "-1\n", void();
  }

  cout << U[0].first << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
