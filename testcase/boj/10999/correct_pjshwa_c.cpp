#include <bits/stdc++.h> 
typedef long long ll;
using namespace std;
const int MAX = 3e6;

class LazySeg {

public:
  LazySeg(int N) {
    n = N;
    for (int i = 0; i < n; i++) cin >> arr[i];
    __init(0, n - 1, 0);
  }

  void update(int L, int R, ll diff) {
    updateRange(0, 0, n - 1, L, R, diff);
  }

  ll query(int L, int R) {
    return getSum(0, n - 1, L, R, 0);
  }

private:
  int n;
  ll tree[MAX], lazy[MAX], arr[MAX];

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) { 
      tree[si] = arr[ss];
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
  }

  void updateLazy(int si, int ss, int se) {
    if (lazy[si] != 0) {
      tree[si] += (se - ss + 1) * lazy[si];

      if (ss != se) {
        lazy[si * 2 + 1] += lazy[si];
        lazy[si * 2 + 2] += lazy[si];
      }
      lazy[si] = 0;
    }
  }
    
  void updateRange(int si, int ss, int se, int us, int ue, ll diff) {
    updateLazy(si, ss, se);

    if (ss > se || ss > ue || se < us) return;

    if (ss >= us && se <= ue) {
      tree[si] += diff * (se - ss + 1);

      if (ss != se) { 
        lazy[si * 2 + 1] += diff;
        lazy[si * 2 + 2] += diff;
      }
      return;
    }

    int mid = (ss + se) / 2;
    updateRange(si * 2 + 1, ss, mid, us, ue, diff);
    updateRange(si * 2 + 2, mid + 1, se, us, ue, diff);

    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
  }
    
  ll getSum(int ss, int se, int qs, int qe, int si) {
    updateLazy(si, ss, se);

    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return getSum(ss, mid, qs, qe, 2 * si + 1) + getSum(mid + 1, se, qs, qe, 2 * si + 2);
  }

};
  
void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, m, k;
  cin >> n >> m >> k;
  LazySeg ls(n);

  m += k;
  while (m--) {
    ll a, b, c, d;
    cin >> a >> b >> c;
    if (a == 1) {
      cin >> d;
      ls.update(b - 1, c - 1, d);
    }
    else cout << ls.query(b - 1, c - 1) << '\n';
  }

}
