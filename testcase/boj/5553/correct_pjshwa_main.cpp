#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAXV = 1e5, INF = 0x3f3f3f3f;

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tree.resize(2 * flag);
  }

  void add(int P, int val) {
    __add(0, 0, n - 1, P, val);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n, flag;
  vector<ll> tree;

  void __add(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] += val;
      return;
    }

    int mid = (ss + se) / 2;
    __add(si * 2 + 1, ss, mid, p, val);
    __add(si * 2 + 2, mid + 1, se, p, val);

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

void solve() {
  int N;
  cin >> N;
  vector<pii> A(N);
  for (int i = 0; i < N; i++) cin >> A[i].first >> A[i].second;
  sort(A.begin(), A.end(), [] (const pii& a, const pii& b) {
    if (a.second == b.second) return a.first < b.first;
    return a.second > b.second;
  });

  SegmentTree ssum(MAXV + 1), scnt(MAXV + 1);

  ll vi = 0, ans = 0;
  set<int> pre;
  for (int b = MAXV; b >= 1; b--) {
    while (vi < N && A[vi].second == b) {
      int v = A[vi].first;
      ssum.add(v, v);
      scnt.add(v, 1);
      pre.insert(v);
      vi++;
    }

    int left = 0, right = MAXV + 1;
    while (left < right) {
      int mid = (left + right) / 2;

      ll csum = ssum.query(0, mid), ccnt = scnt.query(0, mid);
      if (csum <= ccnt * b) left = mid + 1;
      else right = mid;
    }

    auto it = pre.upper_bound(left - 1);
    if (it == pre.end()) ans = max(ans, scnt.query(0, left - 1));
    else {
      ll val = *it;
      ll prev_tsum = ssum.query(0, val - 1), prev_tcnt = scnt.query(0, val - 1);

      left = 0, right = scnt.query(0, val) + 1;
      while (left < right) {
        int mid = (left + right) / 2;

        if (prev_tsum + val * mid <= (prev_tcnt + mid) * b) left = mid + 1;
        else right = mid;
      }

      ans = max(ans, prev_tcnt + left - 1);
    }

  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
