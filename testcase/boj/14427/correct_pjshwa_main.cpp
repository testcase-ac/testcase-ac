#include <bits/stdc++.h>
#define ll long long
#define pll pair<ll, ll>
using namespace std;

const ll MAX = 1e9 + 7;

struct Seg {
  int flag;
  vector<pll> t;

  void build(int n) {
    for (flag = 1; flag < n; flag <<= 1);
    t.resize(2 * flag);

    ll k;
    for (int i = flag; i < flag + n; i++) {
      cin >> k;
      t[i] = { k, i - flag + 1 };
    }
    for (int i = flag - 1; i >= 1; i--) t[i] = min(t[i << 1], t[i << 1 | 1]);
  }

  void modify(int p, int value) {
    for (t[p += flag - 1] = { value, p }; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]);
  }

  pll query(int L, int R) {
    return query(L, R, 1, 1, flag);
  }

  pll query(int L, int R, int n, int nL, int nR) {
    if (R < nL || nR < L) return { MAX, -1 };
    if (L <= nL && nR <= R) return t[n];

    int mid = (nL + nR) / 2;
    return min(query(L, R, n << 1, nL, mid), query(L, R, n << 1 | 1, mid + 1, nR));
  }
} seg;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n, m; ll a, b, c; cin >> n;
  seg.build(n);

  cin >> m;

  while (m--) {
    cin >> a;
    if (a == 2) cout << seg.query(1, n).second << '\n';
    else {
      cin >> b >> c;
      seg.modify(b, c);
    }
  }

  return 0;
}
