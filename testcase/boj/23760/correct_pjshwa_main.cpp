#include <bits/stdc++.h> 
using namespace std;

const int MAX = 1 << 18;
int tree[MAX];

class SegmentTree {

public:
  SegmentTree() {
    n = MAX >> 1;
  }

  void inc(int P) {
    __add(0, 0, n - 1, P, 1);
  }

  void dec(int P) {
    __add(0, 0, n - 1, P, -1);
  }

  int kth(int k) {
    return __kth(0, n - 1, 1, k);
  }

private:
  int n;

  void __add(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] += val;
      return;
    }

    int mid = (ss + se) / 2;
    __add(si * 2 + 1, ss, mid, p, val);
    __add(si * 2 + 2, mid + 1, se, p, val);

    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
  }

  int __kth(int L, int R, int i, int k) {
    if (L == R) return L;

    int mid = (L + R) / 2, qr = tree[(i << 1) - 1];
    if (qr >= k) return __kth(L, mid, i << 1, k);
    else return __kth(mid + 1, R, (i << 1) + 1, k - qr);
  }

};

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  SegmentTree s;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    s.inc(x);
  }

  int w[m], b[m];
  for (int i = 0; i < m; i++) cin >> w[i];
  for (int i = 0; i < m; i++) cin >> b[i];

  for (int i = 0; i < m; i++) {
    int p = s.kth(n + 1 - b[i]);
    if (p < w[i]) return cout << "0\n", 0;

    s.dec(p);
    s.inc(p - w[i]);
  }
  cout << "1\n";
}
