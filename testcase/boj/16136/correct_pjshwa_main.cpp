#include <bits/stdc++.h> 
typedef long long ll;
using namespace std;

const int MAX = 3e5;
int a[MAX], f[1'000'001];

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
    __init(0, N - 1, 0);
  }

  void update_conditional(int L, int R) {
    if (__mquery(0, n - 1, L, R, 0) <= 2) return;
    if (L == R) {
      __update(0, 0, n - 1, L, f[query(L, L)]);
      return;
    }

    int mid = (L + R) / 2;
    update_conditional(L, mid);
    update_conditional(mid + 1, R);
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

  for (int i = 1; i <= 1e6; i++) for (int j = i; j <= 1e6; j += i) f[j]++;

  int n, q;
  cin >> n >> q;
  for (int i = 0; i < n; i++) cin >> a[i];
  SegmentTree ss(n);

  while (q--) {
    int t, ai, bi;
    cin >> t >> ai >> bi;
    ai--;
    bi--;
    if (t == 1) ss.update_conditional(ai, bi);
    else cout << ss.query(ai, bi) << '\n';
  }
}
