#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int ta[1 << 17], tw[1 << 17], te[1 << 17], tn[1 << 17];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
  }

  void update(int P, int val) {
    __update(0, 0, n - 1, P, val);
  }

private:
  int n;
    
  void __update(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      ta[si] = val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    int left = si * 2 + 1, right = si * 2 + 2;
    ta[si] = max(ta[left] + te[right], tw[left] + ta[right]);
    tw[si] = max(tw[left] + tw[right], ta[left] + tn[right]);
    te[si] = max(te[left] + te[right], tn[left] + ta[right]);
    tn[si] = max(te[left] + tn[right], tn[left] + tw[right]);
  }
};

int main() {
  fast_io();

  int n, q;
  cin >> n >> q;
  SegmentTree s(n);
  for (int i = 0; i < n; i++) {
    int y;
    cin >> y;
    s.update(i, y);
  }

  ll ans = 0;
  while (q--) {
    int a, b;
    cin >> a >> b;
    s.update(a - 1, b);
    ans += ta[0];
  }

  cout << ans << '\n';
}
