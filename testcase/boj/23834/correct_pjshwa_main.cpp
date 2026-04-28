#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

const int MAX = 1 << 20;
const ll INF = 1e9 + 7;
ll tmin[MAX];
int a[MAX], b[MAX];

class SegmentTreeMin {

public:
  SegmentTreeMin(int N) {
    n = N;
  }

  void update(int P, ll val) {
    __update(0, 0, n - 1, P, val);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void __update(int si, int ss, int se, int p, ll val) {
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

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> b[i];
  SegmentTreeMin s(n);

  ll ans = 0;
  for (int i = 0; i < m; i++) ans += a[i];
  ans += b[m - 1];

  ll csum = ans, cmin;
  for (int i = 0; i < n; i++) {
    if (i >= m) cmin = s.query(i - m, i - 1) + a[i];
    else cmin = a[i];

    csum += a[i + m];
    csum += (b[i + m] - b[i + m - 1]);
    ans = max(ans, csum - 2 * cmin);
    s.update(i, cmin);
  }

  cout << ans << '\n';
}
