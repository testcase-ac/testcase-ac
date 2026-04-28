#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Seg {
  int flag;  // array size
  vector<ll> t;

  void build(int N) {
    for (flag = 1; flag < N; flag <<= 1);
    t.resize(2 * flag);

    for (int i = flag; i < flag + N; i++) cin >> t[i];
    for (int i = flag - 1; i >= 1; i--) t[i] = gcd(t[i << 1], t[i << 1 | 1]);
  }
  void modify(int p, int value) {  // set value at position p
    for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = gcd(t[p], t[p ^ 1]);
  }
  ll query(int L, int R) {
    return query(L, R, 1, 1, flag);
  }
  ll query(int L, int R, int n, int nL, int nR) {  // sum on interval [L, R]
    if (R < nL || nR < L) return 0;
    if (L <= nL && nR <= R) return t[n];

    int mid = (nL + nR) / 2;
    return gcd(query(L, R, n << 1, nL, mid), query(L, R, n << 1 | 1, mid + 1, nR));
  }
} seg;

ll rec(int l, int r) {
  int s = r - l + 1;
  if (s == 1) return seg.query(l, r);
  else {
    s /= 2;
    return max(rec(l + s, r) + seg.query(l, l + s - 1), rec(l, l + s - 1) + seg.query(l + s, r));
  }
}

int main() {
  cin.tie(NULL); cout.tie(NULL);
  ios_base::sync_with_stdio(false);

  int N;
  cin >> N;
  seg.build(N);
  cout << rec(1, N);
}
