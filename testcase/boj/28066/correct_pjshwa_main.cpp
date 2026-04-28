#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; cin >> N >> K;

  queue<int> E;
  for (int i = 1; i <= N; i++) E.push(i);

  while (1) {
    if (E.size() < K) return cout << E.front(), void();

    E.push(E.front()); E.pop();
    for (int i = 0; i < K - 1; i++) E.pop();
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
