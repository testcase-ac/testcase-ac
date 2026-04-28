#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, Q;
  cin >> N >> Q;

  priority_queue<ll, vector<ll>, greater<ll>> pq;
  int zc = 0;
  for (int i = 0; i < N; i++) {
    int x;
    cin >> x;
    if (x == 0) zc++;
    else pq.push(x);
  }

  while (Q--) {
    int x, y;
    cin >> x >> y;
    if (y == 1) continue;
    else if (y == 0) {
      while (!pq.empty() && pq.top() <= x) {
        pq.pop();
        zc++;
      }
    }
    else {
      vector<ll> s;
      while (!pq.empty() && pq.top() <= x) {
        s.push_back(pq.top() * y);
        pq.pop();
      }
      while (!s.empty()) {
        pq.push(s.back());
        s.pop_back();
      }
    }
  }

  vector<ll> s;
  while (!pq.empty()) {
    s.push_back(pq.top());
    pq.pop();
  }
  for (int i = 0; i < zc; i++) cout << "0 ";
  for (ll e : s) cout << e << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
