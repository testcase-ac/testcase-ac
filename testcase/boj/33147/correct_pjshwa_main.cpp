#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e6;
int A[MAXN];

void solve() {
  int N, K; cin >> N >> K;
  K = __gcd(N, K);
  vector<int> R[K];
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
    R[i % K].push_back(A[i]);
  }
  for (int i = 0; i < K; ++i) {
    sort(R[i].begin(), R[i].end());
    reverse(R[i].begin(), R[i].end());
  }
  for (int i = 0; i < N; ++i) {
    int e = R[i % K].back(); R[i % K].pop_back();
    A[i] = e;
  }

  bool ok = true;
  for (int i = 0; i < N - 1; ++i) {
    if (A[i] > A[i + 1]) {
      ok = false;
      break;
    }
  }
  cout << (ok ? "YES" : "NO") << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
