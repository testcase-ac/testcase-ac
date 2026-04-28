#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define compress(x) sort(all(x)), (x).erase(unique(all(x)), (x).end())
#define getidx(v, x) (lower_bound(all(v), x) - v.begin())
typedef long long ll;
using namespace std;

const int MAX = 1e5;
ll tree[1 << 18], lazy[1 << 18];
vector<int> cpoints;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

class LazySeg {

public:
  LazySeg(int N) {
    n = N;
  }

  void update(int L, int R, ll val) {
    __update_range(0, 0, n - 1, L, R, val);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void __update_lazy(int si, int ss, int se) {
    if (lazy[si] != 0) {
      tree[si] += (cpoints[se + 1] - cpoints[ss]) * lazy[si];

      if (ss != se) {
        lazy[si * 2 + 1] += lazy[si];
        lazy[si * 2 + 2] += lazy[si];
      }
      lazy[si] = 0;
    }
  }

  void __update_range(int si, int ss, int se, int us, int ue, ll val) {
    __update_lazy(si, ss, se);

    if (ss > se || ss > ue || se < us) return;

    if (ss >= us && se <= ue) {
      lazy[si] = val;
      __update_lazy(si, ss, se);
      return;
    }

    int mid = (ss + se) / 2;
    __update_range(si * 2 + 1, ss, mid, us, ue, val);
    __update_range(si * 2 + 2, mid + 1, se, us, ue, val);

    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    __update_lazy(si, ss, se);

    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }
};

int main() {
  fast_io();

  int q;
  cin >> q;
  vector<tuple<int, int, int>> updates;
  vector<tuple<int, int, int, int>> queries;

  int qx = 0;
  while (q--) {
    int qi, x, y, z;
    cin >> qi >> x >> y >> z;
    cpoints.push_back(x);
    cpoints.push_back(y + 1);

    if (qi == 1) updates.push_back({x, y, z});
    else queries.push_back({z, qx++, x, y});
  }
  sort(all(queries));
  compress(cpoints);

  LazySeg s(MAX);
  vector<ll> ans(qx);
  int qi = 0;
  int usz = updates.size(), qsz = queries.size();
  for (int i = 1; i <= usz; i++) {
    auto [x, y, z] = updates[i - 1];
    s.update(getidx(cpoints, x), getidx(cpoints, y + 1) - 1, z);
    while (qi < qsz && get<0>(queries[qi]) <= i) {
      auto [z, qn, x, y] = queries[qi++];
      ans[qn] = s.query(getidx(cpoints, x), getidx(cpoints, y + 1) - 1);
    }
  }
  for (auto a : ans) cout << a << '\n';
}
