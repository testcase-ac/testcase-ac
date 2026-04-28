#include <bits/stdc++.h> 
typedef long long ll;
using namespace std;
const int MAX = 2e6;

ll tree[MAX], lazy[MAX], arr[MAX];

void updateLazy(int si, int ss, int se) {
  if (lazy[si] != 0) {
    if ((se - ss + 1) & 1) tree[si] ^= lazy[si];

    if (ss != se) {
      lazy[si * 2 + 1] ^= lazy[si];
      lazy[si * 2 + 2] ^= lazy[si];
    }
    lazy[si] = 0;
  }
}
  
void updateRange(int si, int ss, int se, int us, int ue, ll diff) {
  updateLazy(si, ss, se);

  if (ss > se || ss > ue || se < us) return;

  if (ss >= us && se <= ue) {
    if ((se - ss + 1) & 1) tree[si] ^= diff;

    if (ss != se) { 
      lazy[si * 2 + 1] ^= diff;
      lazy[si * 2 + 2] ^= diff;
    }
    return;
  }

  int mid = (ss + se) / 2;
  updateRange(si * 2 + 1, ss, mid, us, ue, diff);
  updateRange(si * 2 + 2, mid + 1, se, us, ue, diff);

  tree[si] = tree[si * 2 + 1] ^ tree[si * 2 + 2];
} 

ll getXor(int ss, int se, int qs, int qe, int si) {
  updateLazy(si, ss, se);

  if (ss > se || ss > qe || se < qs) return 0;
  if (ss >= qs && se <= qe) return tree[si];

  int mid = (ss + se) / 2;
  return getXor(ss, mid, qs, qe, 2 * si + 1) ^ getXor(mid + 1, se, qs, qe, 2 * si + 2);
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

  tree[si] = tree[si * 2 + 1] ^ tree[si * 2 + 2];
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, m, a, b, c, d;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> arr[i];
  constructST(0, n - 1, 0);

  cin >> m;
  while (m--) {
    cin >> a >> b;
    if (a == 1) {
      cin >> c >> d;
      updateRange(0, 0, n - 1, b, c, d);
    }
    else cout << getXor(0, n - 1, b, b, 0) << '\n';
  }
}
