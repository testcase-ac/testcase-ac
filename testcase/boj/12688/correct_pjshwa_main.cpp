#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int rem[MAX + 1];
int tc;

class Rect {
public:
  int top, bottom, left, right;
  bool init = false;

  Rect() {}
  Rect merge(int x, int y) {
    if (init) {
      top = min(top, y);
      bottom = max(bottom, y);
      left = min(left, x);
      right = max(right, x);
    }
    else {
      top = bottom = y;
      left = right = x;
      init = true;
    }
    return *this;
  }
  bool inside(int x, int y) {
    if (!init) return false;
    return y >= top && y <= bottom && x >= left && x <= right;
  }
};

void solve() {
  cout << "Case #" << ++tc << ":\n";

  int n;
  cin >> n;

  vector<pii> nq;
  Rect o;
  for (int i = 0; i < n; i++) {
    int hi, wi;
    string s;
    cin >> hi >> wi >> s;
    if (s == "NOT") {
      cin >> s;
      nq.push_back({hi, wi});
    }
    else o.merge(hi, wi);
  }

  int q;
  cin >> q;
  while (q--) {
    int hi, wi;
    cin >> hi >> wi;

    if (o.inside(hi, wi)) {
      cout << "BIRD\n";
      continue;
    }

    bool found = false;
    Rect u = o;
    u.merge(hi, wi);

    for (auto [hs, ws] : nq) {
      if (u.inside(hs, ws)) {
        found = true;
        break;
      }
    }

    cout << (found ? "NOT BIRD" : "UNKNOWN") << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
