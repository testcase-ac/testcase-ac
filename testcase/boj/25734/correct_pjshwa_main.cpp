#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int Q;
  cin >> Q;

  set<pii> S;
  ll run = 0;
  while (Q--) {
    int op, x;
    cin >> op >> x;
    if (op == 1) {
      bool s = false, e = false;

      auto it1 = S.lower_bound({x, 0});
      auto it2 = it1;
      if (it2 != S.begin()) --it2;

      if (it1 != S.end() && it1->first == x + 1) e = true;
      if (it1 != it2 && it2->second == x - 1) s = true;

      if (s) {
        if (e) {
          int ns = it2->first, ne = it1->second;
          S.insert({ns, ne});

          ll d1 = it1->second - it1->first + 1;
          ll d2 = it2->second - it2->first + 1;
          ll nd = ne - ns + 1;
          run -= d1 * (d1 + 1) / 2;
          run -= d2 * (d2 + 1) / 2;
          run += nd * (nd + 1) / 2;

          S.erase(it1);
          S.erase(it2);
        }
        else {
          int ns = it2->first, ne = x;
          S.insert({ns, ne});

          ll d = it2->second - it2->first + 1;
          ll nd = ne - ns + 1;
          run -= d * (d + 1) / 2;
          run += nd * (nd + 1) / 2;

          S.erase(it2);
        }
      }
      else {
        if (e) {
          int ns = x, ne = it1->second;
          S.insert({ns, ne});

          ll d = it1->second - it1->first + 1;
          ll nd = ne - ns + 1;
          run -= d * (d + 1) / 2;
          run += nd * (nd + 1) / 2;

          S.erase(it1);
        }
        else {
          S.insert({x, x});
          run += 1;
        }
      }
    }
    if (op == 2) {
      auto it = S.upper_bound({x, INF});
      it--;

      int os = it->first, oe = it->second;
      if (x - 1 >= os) S.insert({os, x - 1});
      if (x + 1 <= oe) S.insert({x + 1, oe});

      ll d = oe - os + 1;
      ll nd1 = x - 1 - os + 1;
      ll nd2 = oe - (x + 1) + 1;
      run -= d * (d + 1) / 2;
      run += nd1 * (nd1 + 1) / 2;
      run += nd2 * (nd2 + 1) / 2;

      S.erase(it);
    }

    cout << run << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
