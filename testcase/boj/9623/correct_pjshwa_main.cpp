#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int tree[1 << 21];

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
  }

  void add(int P, int val) {
    __add(0, 0, n - 1, P, val);
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

    int left = si * 2 + 1, right = si * 2 + 2;
    tree[si] = tree[left] + tree[right];
  }

  int __kth(int L, int R, int i, int k) {
    if (L == R) return L;

    int mid = (L + R) / 2, qr = tree[(i << 1) - 1];
    if (qr >= k) return __kth(L, mid, i << 1, k);
    else return __kth(mid + 1, R, (i << 1) + 1, k - qr);
  }
};

void solve() {
  int n, x;
  cin >> n >> x;

}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
