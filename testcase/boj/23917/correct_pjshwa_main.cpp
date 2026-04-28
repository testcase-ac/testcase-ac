#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N, X; cin >> N >> X;

  vector<pii> A;
  for (int i = 1; i <= N; i++) {
    int v; cin >> v;
    A.emplace_back((v - 1) / X, i);
  }
  sort(A.begin(), A.end());

  for (auto& [_, i] : A) cout << i << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
