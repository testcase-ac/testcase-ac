#include <bits/stdc++.h> 
typedef long long ll;
using namespace std;
const int MAX = 3e5;

ll tree[MAX], lazy[MAX], arr[MAX];

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
  
void constructST(int ss, int se, int si) {
  if (ss > se) return;

  if (ss == se) { 
    tree[si] = arr[ss];
    return;
  }

  int mid = (ss + se) / 2;
  constructST(ss, mid, si * 2 + 1);
  constructST(mid + 1, se, si * 2 + 2);

  tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
}
  
void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int LIM = 1e5;
int main() {
  fast_io();

  int n, l, r;
  cin >> n;
  constructST(0, LIM - 1, 0);

  int ls, rs;
  for (int i = 1; i <= n; i++) {
    cin >> l >> r;
    ls = getSum(0, LIM - 1, l - 1, l - 1, 0);
    rs = getSum(0, LIM - 1, r - 1, r - 1, 0);
    updateRange(0, 0, LIM - 1, l - 1, l - 1, -ls);
    updateRange(0, 0, LIM - 1, r - 1, r - 1, -rs);
    updateRange(0, 0, LIM - 1, l, r - 2, 1);

    cout << ls + rs << '\n';
  }
}
