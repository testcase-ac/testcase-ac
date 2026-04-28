#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using tll = tuple<ll, ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tree.resize(2 * flag);
  }

  void update(int P, int val) {
    __update(0, 0, n - 1, P, val);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n, flag;
  vector<ll> tree;

  void __update(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] = val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }
};

const int MAX = 2e5;
ll A[MAX + 10], P[MAX + 10];
tll func[MAX + 10];

void calc_func(int i) {
  if (i == 0) {
    if (A[0] == A[1]) func[i] = {0, 0, A[0]};
    else func[i] = {0, A[1] - A[0], A[0]};
  }
  else {
    ll a = A[i + 1] - A[i] - P[i];
    ll b = P[i] - a * 2 * i;
    ll c = A[i] - a * i * i - b * i;
    func[i] = {a, b, c};
  }

  auto [a, b, c] = func[i];
  P[i + 1] = a * 2 * (i + 1) + b;
}

ll eval3(ll a, ll b, ll c, ll x) {
  return a * x * x * x + b * x * x + c * x;
}

ll calc_area6(int i) {
  auto [a, b, c] = func[i];
  ll rhs = eval3(2 * a, 3 * b, 6 * c, i + 1);
  ll lhs = eval3(2 * a, 3 * b, 6 * c, i);
  return (rhs - lhs);
}

void print_func(int i) {
  auto [a, b, c] = func[i];
  cout << a << "x^2 + " << b << "x + " << c << '\n';
}

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i <= N; i++) cin >> A[i];

  SegmentTree area6(N);
  for (int i = 0; i < N; i++) {
    calc_func(i);
    area6.update(i, calc_area6(i));
    cout << "i = " << i << ", P[i] = " << P[i] << ", area6 = " << calc_area6(i) << '\n';
    print_func(i);
  }

  int Q;
  cin >> Q;
  while (Q--) {
    int op, x, y;
    cin >> op >> x >> y;
    if (op == 1) {
      A[x] = y;
      for (int i = x - 1; i <= N; i++) {
        if (i < 0) continue;

        calc_func(i);
        area6.update(i, calc_area6(i));
        cout << "i = " << i << ", P[i] = " << P[i] << ", area6 = " << calc_area6(i) << '\n';
        print_func(i);
      }
    }
    if (op == 2) {
      cout << area6.query(x, y - 1) << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
