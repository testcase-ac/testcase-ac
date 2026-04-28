#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 1e5, INF = 1e18;
ll d[MAX + 1][11];

class LazySegMax {

public:
  LazySegMax(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tree.resize(2 * flag);
    lazy.resize(2 * flag);
  }

  void update(int L, int R, ll val) {
    __update_range(0, 0, n - 1, L, R, val);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n, flag;
  vector<ll> tree, lazy;

  void __update_lazy(int si, int ss, int se) {
    if (lazy[si] != 0) {
      tree[si] += lazy[si];

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

    tree[si] = max(tree[si * 2 + 1], tree[si * 2 + 2]);
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    __update_lazy(si, ss, se);

    if (ss > se || ss > qe || se < qs) return -INF;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return max(__query(ss, mid, qs, qe, 2 * si + 1), __query(mid + 1, se, qs, qe, 2 * si + 2));
  }
};

void solve() {
  int N, M; cin >> N >> M;

  vector<pll> A(N + 1);
  for (int i = 1; i <= N; i++) {
    int hi, si; cin >> hi >> si;
    A[i] = {hi, si};
  }

  LazySegMax rxq(N + 1);
  rxq.update(0, N, -INF);
  rxq.update(0, 0, INF);

  auto reset_rxq = [&]() {
    for (int i = 0; i <= N; i++) rxq.update(i, i, -rxq.query(i, i));
  };

  for (int m = 1; m <= M; m++) {
    ll acc = 0, hgt = -1;
    stack<tuple<ll, ll, ll, ll>> T;

    for (int i = 1; i <= N; i++) {
      auto [hi, si] = A[i];
      while (!T.empty()) {
        auto [hj, sj, s, e] = T.top();
        if (hj < hi) {
          rxq.update(s - 1, e - 1, -sj);
          T.pop();
        }
        else break;
      }

      ll hk, sk, s, e = 0;
      if (T.size()) tie(hk, sk, s, e) = T.top();

      if (hi == hk) {
        rxq.update(s - 1, i - 1, si);
        T.push({hi, si, s, i});
      }
      else {
        rxq.update(e, i - 1, si);
        T.push({hi, si, e + 1, i});
      }

      d[i][m] = rxq.query(0, i - 1);
      // cout << "d[" << i << "][" << m << "] = " << d[i][m] << endl;
    }

    reset_rxq();
    for (int i = 0; i <= N; i++) rxq.update(i, i, d[i][m]);
  }

  cout << d[N][M] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
