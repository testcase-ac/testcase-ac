#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, D; cin >> N >> D;

  priority_queue<int, vector<int>, greater<int>> pA, pB;

  int maxx = 0;
  for (int i = 0; i < N; ++i) {
    int ai, xi; cin >> ai >> xi;
    if (ai == 1) {
      pA.push(xi);
      maxx = max(maxx, xi);
    }
    else {
      pB.push(xi);
    }
  }

  while (!pB.empty()) {
    while (!pA.empty() && pA.top() < D) {
      D += pA.top();
      pA.pop();
    }
    if (D > maxx) return cout << N << '\n', void();

    D *= pB.top(); pB.pop();
    if (D > maxx) return cout << N << '\n', void();
  }

  while (!pA.empty() && pA.top() < D) {
    D += pA.top();
    pA.pop();
  }

  cout << N - pA.size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
