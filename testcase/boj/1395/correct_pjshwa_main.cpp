#include <bits/stdc++.h> 
using namespace std;

const int MAX = 3e5;
int tree[MAX];
bool lazy[MAX];

void update_lazy(int si, int ss, int se) {
  if (lazy[si]) {
    tree[si] = (se - ss + 1) - tree[si];

    if (ss != se) {
      lazy[si * 2 + 1] = !lazy[si * 2 + 1];
      lazy[si * 2 + 2] = !lazy[si * 2 + 2];
    }
    lazy[si] = 0;
  }
}
  
void update_range(int si, int ss, int se, int us, int ue) {
  update_lazy(si, ss, se);

  if (ss > se || ss > ue || se < us) return;

  if (ss >= us && se <= ue) {
    tree[si] = (se - ss + 1) - tree[si];

    if (ss != se) { 
      lazy[si * 2 + 1] = !lazy[si * 2 + 1];
      lazy[si * 2 + 2] = !lazy[si * 2 + 2];
    }
    return;
  }

  int mid = (ss + se) / 2;
  update_range(si * 2 + 1, ss, mid, us, ue);
  update_range(si * 2 + 2, mid + 1, se, us, ue);

  tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
}

int query(int ss, int se, int qs, int qe, int si) {
  update_lazy(si, ss, se);

  if (ss > se || ss > qe || se < qs) return 0;
  if (ss >= qs && se <= qe) return tree[si];

  int mid = (ss + se) / 2;
  return query(ss, mid, qs, qe, 2 * si + 1) + query(mid + 1, se, qs, qe, 2 * si + 2);
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, m, a, b, c;
  cin >> n >> m;

  while (m--) {
    cin >> a >> b >> c;
    if (a == 0) update_range(0, 0, n - 1, b - 1, c - 1);
    else cout << query(0, n - 1, b - 1, c - 1, 0) << '\n';
  }
}
