#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXG = 100, MAXH = 10000;
ll prices[MAXH + 1], stocks[MAXH + 1];
vector<int> G[MAXG + 1];
map<string, int> id_by_name;
int it;

void solve() {
  ll N, M, Q; cin >> N >> M >> Q;
  for (int i = 0; i < N; ++i) {
    int g, p; string name; cin >> g >> name >> p;
    id_by_name[name] = it;
    prices[it] = p;
    G[g].push_back(it++);
  }

  ll tot = M;
  while (Q--) {
    int op; cin >> op;
    if (op == 1) {
      string name; ll q; cin >> name >> q;
      int c = id_by_name[name];

      if (prices[c] * q > M) continue;
      else {
        M -= prices[c] * q;
        stocks[c] += q;
      }
    }
    if (op == 2) {
      string name; ll q; cin >> name >> q;
      int c = id_by_name[name];
      q = min(q, stocks[c]);
      stocks[c] -= q;
      M += prices[c] * q;
    }
    if (op == 3) {
      string name; ll p; cin >> name >> p;
      int c = id_by_name[name];

      ll np = prices[c] + p;
      tot += stocks[c] * (np - prices[c]);
      prices[c] = np;
    }
    if (op == 4) {
      int g, p; cin >> g >> p;
      for (int c : G[g]) {
        ll np = prices[c] + p;
        tot += stocks[c] * (np - prices[c]);
        prices[c] = np;
      }
    }
    if (op == 5) {
      int g, p; cin >> g >> p;
      for (int c : G[g]) {
        ll np = ((100 + p) * prices[c] / 100) / 10 * 10;
        tot += stocks[c] * (np - prices[c]);
        prices[c] = np;
      }
    }
    if (op == 6) {
      cout << M << '\n';
    }
    if (op == 7) {
      // ll acc = 0;
      // for (int c = 0; c < N; ++c) acc += prices[c] * stocks[c];
      // cout << acc + M << '\n';
      cout << tot << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
