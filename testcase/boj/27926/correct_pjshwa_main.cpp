#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
priority_queue<pii> L[MAX + 1];

void solve() {
  int N, M; cin >> N >> M;

  priority_queue<tii> T;
  vector<tii> A(M);
  for (int i = 0; i < M; i++) {
    int x, y, d; cin >> x >> y >> d;
    A[i] = {x, y, d};

    L[x].emplace(d, y);
    L[y].emplace(d, x);
    T.emplace(d, x, y);
  }

  ll ans = 0;
  for (int i = 0; i < M; i++) {
    priority_queue<pii> W1, W2;

    auto [x, y, d] = A[i];

    ll z1x = -1, z2x = -2, d1x = 0, d2x = 0;
    while (!L[x].empty()) {
      auto [d, yc] = L[x].top();
      W1.push(L[x].top());
      L[x].pop();

      if (y == yc) continue;
      tie(d1x, z1x) = pii(d, yc);
      break;
    }
    while (!L[x].empty()) {
      auto [d, yc] = L[x].top();
      W1.push(L[x].top());
      L[x].pop();

      if (y == yc) continue;
      tie(d2x, z2x) = pii(d, yc);
      break;
    }

    ll z1y = -3, z2y = -4, d1y = 0, d2y = 0;
    while (!L[y].empty()) {
      auto [d, xc] = L[y].top();
      W2.push(L[y].top());
      L[y].pop();

      if (x == xc) continue;
      tie(d1y, z1y) = pii(d, xc);
      break;
    }
    while (!L[y].empty()) {
      auto [d, xc] = L[y].top();
      W2.push(L[y].top());
      L[y].pop();

      if (x == xc) continue;
      tie(d2y, z2y) = pii(d, xc);
      break;
    }

    // cout << "x = " << x << ", y = " << y << ", d = " << d << endl;
    // cout << "z1x = " << z1x << ", z2x = " << z2x << ", d1x = " << d1x << ", d2x = " << d2x << endl;
    // cout << "z1y = " << z1y << ", z2y = " << z2y << ", d1y = " << d1y << ", d2y = " << d2y << endl;

    ll cur;
    if (z1x == z1y) cur = max(d + d1x + d2y, d + d1y + d2x);
    else cur = d + d1x + d1y;

    // cout << "cur = " << cur << endl;
    ans = max(ans, cur);

    while (!W1.empty()) L[x].push(W1.top()), W1.pop();
    while (!W2.empty()) L[y].push(W2.top()), W2.pop();
  }

  for (int i = 1; i <= N; i++) {
    priority_queue<tii> W;
    while (!T.empty()) {
      auto [d, x, y] = T.top();
      if (x == i || y == i) {
        W.push(T.top());
        T.pop();
      }
      else break;
    }

    ll x = -1, y = -1, dt = 0;
    if (!T.empty()) tie(dt, x, y) = T.top();

    ll z1 = -2, z2 = -3, z3 = -4, d1 = 0, d2 = 0, d3 = 0;
    if (!L[i].empty()) tie(d1, z1) = L[i].top(), L[i].pop();
    if (!L[i].empty()) tie(d2, z2) = L[i].top(), L[i].pop();
    if (!L[i].empty()) tie(d3, z3) = L[i].top(), L[i].pop();

    ans = max(ans, d1 + dt);
    ans = max(ans, d1 + d2);

    if (x == z1) {
      if (y == z2) ans = max(ans, d1 + d3 + dt);
      else ans = max(ans, d1 + d2 + dt);
    }
    if (x == z2) {
      if (y == z1) ans = max(ans, d2 + d3 + dt);
      else ans = max(ans, d1 + d2 + dt);
    }
    if (y == z1) {
      if (x == z2) ans = max(ans, d1 + d3 + dt);
      else ans = max(ans, d1 + d2 + dt);
    }
    if (y == z2) {
      if (x == z1) ans = max(ans, d2 + d3 + dt);
      else ans = max(ans, d1 + d2 + dt);
    }

    while (!W.empty()) {
      T.push(W.top());
      W.pop();
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
