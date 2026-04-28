#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 0x3f3f3f3f;

class SegmentTreeMin {

public:
  SegmentTreeMin(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tmin.resize(2 * flag);
  }

  void update(int P, int val) {
    __update(0, 0, n - 1, P, val);
  }

  int query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n, flag;
  vector<int> tmin;

  void __update(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tmin[si] = val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    tmin[si] = min(tmin[si * 2 + 1], tmin[si * 2 + 2]);
  }

  int __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return INF;
    if (ss >= qs && se <= qe) return tmin[si];

    int mid = (ss + se) / 2;
    return min(__query(ss, mid, qs, qe, si * 2 + 1), __query(mid + 1, se, qs, qe, si * 2 + 2));
  }
};


class SegmentTreeMax {

public:
  SegmentTreeMax(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tmax.resize(2 * flag);
  }

  void update(int P, int val) {
    __update(0, 0, n - 1, P, val);
  }

  int query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n, flag;
  vector<int> tmax;

  void __update(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tmax[si] = val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    tmax[si] = max(tmax[si * 2 + 1], tmax[si * 2 + 2]);
  }

  int __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return -INF;
    if (ss >= qs && se <= qe) return tmax[si];

    int mid = (ss + se) / 2;
    return max(__query(ss, mid, qs, qe, si * 2 + 1), __query(mid + 1, se, qs, qe, si * 2 + 2));
  }
};

const int MAX = 3e5;
SegmentTreeMax sx(MAX + 1);
SegmentTreeMin sm(MAX + 1);

// #include <sys/resource.h>


// void enlarge_stack() {
//   struct rlimit lim;
//   getrlimit(RLIMIT_STACK, &lim);
//   lim.rlim_cur = lim.rlim_max;
//   setrlimit(RLIMIT_STACK, &lim);
// }

bool r(int s, int e, int x, int y) {
  if (s == e) return true;

  // cout << "s = " << s << ", e = " << e << ", x = " << x << ", y = " << y << endl;

  bool ret = false;
  for (int i = s + 1; i <= e; i++) {
    int vl = i - s, vr = e - i + 1;
    if (sm.query(s, i - 1) == y - vl + 1 && sx.query(i, e) == x + vr - 1) {
      ret |= r(s, i - 1, y - vl + 1, y) && r(i, e, x, x + vr - 1);
      break;
    }
    else if (sx.query(s, i - 1) == x + vl - 1 && sm.query(i, e) == y - vr + 1) {
      ret |= r(s, i - 1, x, x + vl - 1) && r(i, e, y - vr + 1, y);
      break;
    }
  }
  return ret;
}

void solve() {
  int N;
  cin >> N;

  vector<int> A(N + 1);
  for (int i = 1; i <= N; i++) {
    cin >> A[i];
    sx.update(i, A[i]);
    sm.update(i, A[i]);
  }

  if (r(1, N, 1, N)) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  fast_io();

  // enlarge_stack();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
