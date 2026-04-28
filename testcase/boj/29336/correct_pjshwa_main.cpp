#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;

  priority_queue<ll> pq;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    pq.push(x);
  }

  ll acc = 0; int Ti, Qi;
  for (int i = 0; i < M; i++) {
    cin >> Ti >> Qi;
    while (acc < Qi) {
      if (pq.empty()) return cout << "-1\n", void();

      acc += pq.top() + Ti;
      pq.pop();
    }
  }

  while (!pq.empty()) {
    acc += pq.top() + Ti;
    pq.pop();
  }
  cout << acc << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
