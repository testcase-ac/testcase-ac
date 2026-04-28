#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX = 2e5, MOD = 1e9 + 7;
vector<int> graph[MAX + 1], tree[1 << 19];
int vs[MAX + 1], ve[MAX + 1], c[MAX + 1], oc[MAX + 1];
bool vis[MAX + 1];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int tick = 0;
void dfs(int v) {
  vis[v] = true;
  vs[v] = ++tick;
  for (int d : graph[v]) {
    if (!vis[d]) dfs(d);
  }
  ve[v] = tick;
}

class MergeSortTree {

public:
  MergeSortTree(int N) {
    n = N;
    __init(0, N - 1, 0);
  }

  int query(int L, int R, int val) {
    return __query(0, n - 1, L, R, 0, val);
  }

private:
  int n;

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) {
      tree[si] = {c[ss]};
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

    vector<int> &lhs = tree[si * 2 + 1], &rhs = tree[si * 2 + 2];
    tree[si].resize(lhs.size() + rhs.size());
    int i = 0, j = 0;
    for (int k = 0; k < lhs.size() + rhs.size(); k++) {
      if (i == lhs.size() || (j < rhs.size() && lhs[i] > rhs[j])) tree[si][k] = rhs[j++];
      else tree[si][k] = lhs[i++]; 
    }
  }

  int __query(int ss, int se, int qs, int qe, int si, int val) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return upper_bound(tree[si].begin(), tree[si].end(), val) - tree[si].begin();

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1, val) + __query(mid + 1, se, qs, qe, 2 * si + 2, val);
  }
};

int main() {
  fast_io();

  int n, q, k;
  cin >> n >> q >> k;
  for (int i = 1; i <= n; i++) cin >> oc[i];
  for (int i = 1; i <= n - 1; i++) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }
  dfs(1);
  for (int i = 1; i <= n; i++) c[vs[i]] = oc[i];

  MergeSortTree mt(n + 1);
  ll ans = 0;
  while (q--) {
    int a, b;
    cin >> a >> b;
    ans = (ans + mt.query(vs[a], ve[a], b)) % MOD;
  }
  cout << ans << '\n';
}
