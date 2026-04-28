#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M, K; cin >> N >> M >> K;
  priority_queue<int> pq;
  for (int i = 0; i < N; ++i) {
    int d; cin >> d;
    pq.push(d);
  }

  int sat = 0;
  vector<int> days;
  while (!pq.empty()) {
    int d = pq.top(); pq.pop();
    sat = (sat / 2) + d;
    days.push_back(sat);

    d -= M;
    if (d > K) pq.push(d);
  }

  cout << days.size() << '\n';
  for (int d : days) cout << d << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
