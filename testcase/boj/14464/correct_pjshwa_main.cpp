#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

struct Cow {
  int si, ei;

  bool operator<(const Cow& rhs) const {
    return ei == rhs.ei ? si < rhs.si : ei < rhs.ei;
  }
};

const int MAX = 2e4;
Cow cows[MAX];

int main() {
  fast_io();

  int c, n, x;
  multiset<int> cm;
  cin >> c >> n;
  for (int i = 0; i < c; i++) cin >> x, cm.insert(x);
  for (int i = 0; i < n; i++) cin >> cows[i].si >> cows[i].ei;
  sort(cows, cows + n);

  int ci = 0, ans = 0;
  for (int i = 0; i < n; i++) {
    auto it = cm.lower_bound(cows[i].si);
    if (it != cm.end() && *it <= cows[i].ei) {
      ans++;
      cm.erase(it);
    }
  }

  cout << ans << '\n';
}
