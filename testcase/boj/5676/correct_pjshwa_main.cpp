#include <bits/stdc++.h> 
typedef long long ll;
using namespace std;
const int MAX = 3e5;

class Seg {

public:
  Seg(int N) {
    n = N;
    for (int i = 0; i < n; i++) cin >> arr[i];
    __init(0, n - 1, 0);
  }

  void update(int P, ll val) {
    __update(0, 0, n - 1, P, val == 0 ? 0 : val / abs(val));
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;
  ll tree[MAX], arr[MAX];

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) {
      tree[si] = arr[ss] == 0 ? 0 : arr[ss] / abs(arr[ss]);
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

    tree[si] = tree[si * 2 + 1] * tree[si * 2 + 2];
  }
    
  void __update(int si, int ss, int se, int p, ll val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] = val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    tree[si] = tree[si * 2 + 1] * tree[si * 2 + 2];
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 1;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) * __query(mid + 1, se, qs, qe, 2 * si + 2);
  }

};
  
void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, k;
  while (cin >> n >> k) {
    Seg s(n);

    while (k--) {
      string op;
      int a, b, res;
      cin >> op >> a >> b;
      if (op == "C") s.update(a - 1, b);
      if (op == "P") {
        res = s.query(a - 1, b - 1);
        if (res == +1) cout << '+';
        if (res == +0) cout << '0';
        if (res == -1) cout << '-'; 
      }
    }

    cout << '\n';
  }

}
