#include <iostream>
#include <set>
#include <algorithm>
#include <numeric>
#include <utility>

using namespace std;

using lint = long long;
using pint = pair<int, int>;
#define x first
#define y second

int N, a[200004], pos[200004];

int main() {
  cin >> N;

  for (int i = 1; i <= N; i++) cin >> a[i];
  for (int i = 1; i <= N; i++) pos[a[i]] = i;

  set<pint> s;
  lint ans = 0;
  function<lint(set<pint>::iterator)> update = [&](auto p) {
    if (p == s.end() or next(p) == s.end() or next(next(p)) == s.end())
      return 0ll;
    if ((p->y < next(p)->y) != (next(p)->y < next(next(p))->y)) return 0ll;
    return p->x * (lint)(N - next(next(p))->x + 1);
  };

  for (int i = 1; i <= N; i++) {
    auto p = s.lower_bound(pint(pos[i], 0));

    if (p != s.begin()) {
      ans += update(prev(p));
      if (prev(p) != s.begin()) ans += update(prev(prev(p)));
    }

    s.emplace(pos[i], i);
    ans += pos[i] * (lint)(N - pos[i] + 1);

    p = s.lower_bound(pint(pos[i], 0));

    ans -= update(p);
    if (p != s.begin()) {
      ans -= update(prev(p));
      if (prev(p) != s.begin()) ans -= update(prev(prev(p)));
    }

    cout << ans << '\n';
  }
}