#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Seg {
  int flag;
  vector<ll> t;

  void build(int n) {
    for (flag = 1; flag < n; flag <<= 1);
    t.resize(2 * flag);

    for (int i = flag; i < flag + n; i++) cin >> t[i];
    for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
  }

  void modify(int p, int value) {
    for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
  }

  ll query(int L, int R) {
    return query(L, R, 1, 1, flag);
  }

  ll query(int L, int R, int n, int nL, int nR) {
    if (R < nL || nR < L) return 0;
    if (L <= nL && nR <= R) return t[n];

    int mid = (nL + nR) / 2;
    return query(L, R, n << 1, nL, mid) + query(L, R, n << 1 | 1, mid + 1, nR);
  }
} seg;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

void swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

int main() {
  fast_io();

  int n, q, x, y, a, b;
  cin >> n >> q;
  seg.build(n);

  while (q--) {
    cin >> x >> y >> a >> b;
    if (x > y) swap(x, y);
    cout << seg.query(x, y) << '\n';
    seg.modify(a, b);
  }
}
