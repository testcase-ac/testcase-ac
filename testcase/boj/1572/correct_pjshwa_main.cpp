#include <bits/stdc++.h> 
using namespace std;

const int MAX = 1 << 19;
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

int qs[250'000];
int main() {
  fast_io();

  SegmentTree s;

  int q, k;
  cin >> q >> k;
  for (int i = 0; i < q; i++) cin >> qs[i];

  long long ans = 0;
  for (int i = 0; i < k; i++) s.inc(qs[i]);
  for (int i = k; i < q; i++) {
    ans += s.kth((k + 1) / 2);
    s.dec(qs[i - k]);
    s.inc(qs[i]);
  }
  cout << ans + s.kth((k + 1) / 2);
}
