#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N; cin >> N;

  map<ll, int> cdist;
  cdist[N] = 0;
  queue<ll> q;
  q.push(N);

  while (!q.empty()) {
    ll v = q.front(); q.pop();

    if (v == 1) {
      cout << cdist[v] << '\n';
      return;
    }

    if (v % 3 == 0 && !cdist.count(v / 3)) {
      cdist[v / 3] = cdist[v] + 1;
      q.push(v / 3);
    }
    if (v % 2 == 0 && !cdist.count(v / 2)) {
      cdist[v / 2] = cdist[v] + 1;
      q.push(v / 2);
    }
    if (!cdist.count(v - 1)) {
      cdist[v - 1] = cdist[v] + 1;
      q.push(v - 1);
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
