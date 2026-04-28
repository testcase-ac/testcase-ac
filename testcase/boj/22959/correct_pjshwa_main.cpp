#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX = 1 << 19;
const ll INF = 1e16;
ll tree[MAX], tmin[MAX], a[MAX];

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
    __init(0, N - 1, 0);
  }

  void update(int P, int val) {
    __update(0, 0, n - 1, P, val);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) {
      tree[si] = a[ss];
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
  }
    
  void __update(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] = val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    int left = si * 2 + 1, right = si * 2 + 2;
    tree[si] = tree[left] + tree[right];
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }
};

class SegmentTreeMin {

public:
  SegmentTreeMin(int N) {
    n = N;
    __init(0, N - 1, 0);
  }

  void update(int P, int val) {
    __update(0, 0, n - 1, P, val);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) {
      tmin[si] = a[ss];
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

    tmin[si] = min(tmin[si * 2 + 1], tmin[si * 2 + 2]);
  }

  void __update(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tmin[si] = val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    int left = si * 2 + 1, right = si * 2 + 2;
    tmin[si] = min(tmin[left], tmin[right]);
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return INF;
    if (ss >= qs && se <= qe) return tmin[si];

    int mid = (ss + se) / 2;
    return min(__query(ss, mid, qs, qe, si * 2 + 1), __query(mid + 1, se, qs, qe, si * 2 + 2));
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
  SegmentTreeMin sm(n);
  SegmentTree sx(n);

  cin >> q;
  while (q--) {
    int op, x, y;
    cin >> op >> x >> y;
    if (op == 1) {
      sm.update(x - 1, y);
      sx.update(x - 1, y);
    }
    else {
      int left, right, mid, dl, dr;

      left = 0, right = x - 1;
      mid = (left + right) / 2;
      while (left < right) {
        if (sm.query(mid, x - 1) < y) left = mid + 1;
        else right = mid;
        mid = (left + right) / 2;
      }
      dl = mid;

      left = x - 1, right = n;
      mid = (left + right) / 2;
      while (left < right) {
        if (sm.query(x - 1, mid) >= y) left = mid + 1;
        else right = mid;
        mid = (left + right) / 2;
      }
      dr = mid - 1;

      cout << sx.query(dl, dr) << '\n';
    }
  }
}
