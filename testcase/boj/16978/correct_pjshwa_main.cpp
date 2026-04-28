#include <bits/stdc++.h> 
typedef long long ll;
using namespace std;

const int MAX = 3e5;
int a[MAX];

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
    __init(0, N - 1, 0);
  }

  void update(int P, ll val) {
    __update(0, 0, n - 1, P, val);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;
  ll tree[MAX], tmax[MAX];

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) {
      tree[si] = a[ss];
      tmax[si] = a[ss];
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
    tmax[si] = max(tmax[si * 2 + 1], tmax[si * 2 + 2]);
  }

  void __update(int si, int ss, int se, int p, ll val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] = val;
      tmax[si] = val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
    tmax[si] = max(tmax[si * 2 + 1], tmax[si * 2 + 2]);
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }

  ll __mquery(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tmax[si];

    int mid = (ss + se) / 2;
    return max(__mquery(ss, mid, qs, qe, 2 * si + 1), __mquery(mid + 1, se, qs, qe, 2 * si + 2));
  }

};

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, q;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  SegmentTree s(n);

  cin >> q;
  queue<pair<int, int>> mq;
  priority_queue<tuple<int, int, int, int>> prq;

  int pqc = 0;
  while (q--) {
    int t, ai, bi, ci;
    cin >> t >> ai >> bi;
    if (t == 1) mq.push({ai, bi});
    else {
      cin >> ci;
      prq.push({-ai, bi, ci, pqc++});
    }
  }

  ll pa[MAX];
  int processed = 0;
  while (!prq.empty()) {
    auto[qk, qs, qe, qi] = prq.top();
    prq.pop();

    while (processed < -qk) {
      auto[mi, mv] = mq.front();
      mq.pop();
      s.update(mi - 1, mv);
      processed++;
    }

    pa[qi] = s.query(qs - 1, qe - 1);
  }

  for (int i = 0; i < pqc; i++) cout << pa[i] << '\n';
}
