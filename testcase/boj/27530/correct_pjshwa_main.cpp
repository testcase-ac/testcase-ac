#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

class LazySegMax {

public:
  LazySegMax(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tree.resize(2 * flag);
    lazy_add.resize(2 * flag);
    lazy_set.resize(2 * flag);
  }

  void update_add(int L, int R, ll val) {
    __update_add(0, 0, n - 1, L, R, val);
  }

  void update_set(int L, int R, ll val) {
    __update_set(0, 0, n - 1, L, R, val);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

  // min point such that query(p, p) >= val
  int lbound(int val) {
    int p = 0, ss = 0, se = n - 1;
    __update_lazy(p, ss, se);
    if (tree[0] < val) return n;

    while (ss != se) {
      __update_lazy(p * 2 + 1, ss, (ss + se) / 2);
      __update_lazy(p * 2 + 2, (ss + se) / 2 + 1, se);

      if (tree[p * 2 + 1] >= val) {
        p = p * 2 + 1;
        se = (ss + se) / 2;
      }
      else {
        p = p * 2 + 2;
        ss = (ss + se) / 2 + 1;
      }
    }
    return ss;
	}

private:
  int n, flag;
  vector<ll> tree, lazy_add, lazy_set;

  void __update_lazy(int si, int ss, int se) {
    if (lazy_set[si] != 0) {
      tree[si] = lazy_set[si];

      if (ss != se) {
        lazy_set[si * 2 + 1] = lazy_set[si];
        lazy_set[si * 2 + 2] = lazy_set[si];
        lazy_add[si * 2 + 1] = lazy_add[si * 2 + 2] = 0;
      }
      lazy_set[si] = 0;
    }
    if (lazy_add[si] != 0) {
      tree[si] += lazy_add[si];

      if (ss != se) {
        lazy_add[si * 2 + 1] += lazy_add[si];
        lazy_add[si * 2 + 2] += lazy_add[si];
      }
      lazy_add[si] = 0;
    }
  }

  void __update_add(int si, int ss, int se, int us, int ue, ll val) {
    __update_lazy(si, ss, se);

    if (ss > se || ss > ue || se < us) return;

    if (ss >= us && se <= ue) {
      lazy_add[si] = val;
      __update_lazy(si, ss, se);
      return;
    }

    int mid = (ss + se) / 2;
    __update_add(si * 2 + 1, ss, mid, us, ue, val);
    __update_add(si * 2 + 2, mid + 1, se, us, ue, val);

    tree[si] = max(tree[si * 2 + 1], tree[si * 2 + 2]);
  }

  void __update_set(int si, int ss, int se, int us, int ue, ll val) {
    __update_lazy(si, ss, se);

    if (ss > se || ss > ue || se < us) return;

    if (ss >= us && se <= ue) {
      lazy_set[si] = val;
      lazy_add[si] = 0;
      __update_lazy(si, ss, se);
      return;
    }

    int mid = (ss + se) / 2;
    __update_set(si * 2 + 1, ss, mid, us, ue, val);
    __update_set(si * 2 + 2, mid + 1, se, us, ue, val);

    tree[si] = max(tree[si * 2 + 1], tree[si * 2 + 2]);
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    __update_lazy(si, ss, se);

    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return max(__query(ss, mid, qs, qe, 2 * si + 1), __query(mid + 1, se, qs, qe, 2 * si + 2));
  }
};

const int MAX = 2e5;
int X[MAX], Y[MAX];
int N, M, K, Q;
vector<pii> L;
vector<tii> queries;

void solve_horizontal() {
  vector<pii> xs;
  for (int i = 0; i < K; i++) xs.emplace_back(L[i].first, i);
  sort(xs.begin(), xs.end());

  LazySegMax pos(K);
  for (int i = 0; i < K; i++) pos.update_add(i, i, xs[i].first);

  for (auto& [x, _, t] : queries) {

    // for (int i = 0; i < K; i++) cout << "pos.query(" << i << ", " << i << ") = " << pos.query(i, i) << ' ';
    // cout << endl;

    int l = pos.lbound(x - t);
    int r = pos.lbound(x + t + 1);

    pos.update_add(0, l - 1, t);
    pos.update_set(l, r - 1, x);
    pos.update_add(r, K - 1, -t);
  }

  for (int i = 0; i < K; i++) {
    X[xs[i].second] = pos.query(i, i);
  }
}

void solve_vertical() {
  vector<pii> ys;
  for (int i = 0; i < K; i++) ys.emplace_back(L[i].second, i);
  sort(ys.begin(), ys.end());

  LazySegMax pos(K);
  for (int i = 0; i < K; i++) pos.update_add(i, i, ys[i].first);

  for (auto& [_, y, t] : queries) {
    int l = pos.lbound(y - t);
    int r = pos.lbound(y + t + 1);

    pos.update_add(0, l - 1, t);
    pos.update_set(l, r - 1, y);
    pos.update_add(r, K - 1, -t);
  }

  for (int i = 0; i < K; i++) {
    Y[ys[i].second] = pos.query(i, i);
  }
}

void solve() {
  cin >> N >> M >> K >> Q;

  L.resize(K);
  for (auto& [x, y] : L) cin >> x >> y;

  queries.resize(Q);
  for (auto& [x, y, t] : queries) cin >> x >> y >> t;

  solve_horizontal();
  solve_vertical();
  for (int i = 0; i < K; i++) cout << X[i] << ' ' << Y[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
