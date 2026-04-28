#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5000;
int A[MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> A[i];

  vector<int> par(N + 1, 0);
  for (int i = 1; i <= N; ++i) par[i] = (A[i] % 2 != i % 2);

  for (int i = 1; i <= N; ++i) {
    cout << "par[" << i << "] = " << par[i] << "\n";
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
