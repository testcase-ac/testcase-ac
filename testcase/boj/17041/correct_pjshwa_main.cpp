#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;

  vector<tuple<string, int, int>> v;
  for (int i = 0; i < N; i++) {
    string op; int s, e;
    cin >> op >> s >> e;
    v.emplace_back(op, s, e);
  }

  {
    int cs = -1, ce = -1, si;
    for (int i = N - 1; i >= 0; i--) {
      auto [op, s, e] = v[i];
      if (op == "on") {
        if (cs == -1) continue;

        cs -= e, ce -= s;
      }
      if (op == "off") {
        if (cs == -1) continue;

        cs += s, ce += e;
      }
      if (op == "none") {
        if (cs == -1) cs = s, ce = e, si = i;
        else cs = max(cs, s), ce = min(ce, e);
      }

      cs = max(cs, 0), ce = max(ce, 0);
    }

    cout << cs << ' ' << ce << '\n';
  }

  {
    int cs = -1, ce = -1, si;
    for (int i = 0; i < N; i++) {
      auto [op, s, e] = v[i];
      if (op == "on") {
        if (cs == -1) continue;

        cs += s, ce += e;
      }
      if (op == "off") {
        if (cs == -1) continue;

        cs -= e, ce -= s;
      }
      if (op == "none") {
        if (cs == -1) cs = s, ce = e, si = i;
        else cs = max(cs, s), ce = min(ce, e);
      }

      cs = max(cs, 0), ce = max(ce, 0);
    }

    cout << cs << ' ' << ce << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
