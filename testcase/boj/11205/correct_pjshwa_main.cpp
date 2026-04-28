#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int M, L, TM, TL;
map<tuple<int, int, int, int>, bool> d;
bool dfs(int pos, int ct, int cmp, int clp) {
  if (d.count({pos, ct, cmp, clp})) return d[{pos, ct, cmp, clp}];

  if (ct > TM && ct > TL) return d[{pos, ct, cmp, clp}] = false;
  if (cmp == M && clp == L) return d[{pos, ct, cmp, clp}] = true;

  bool ret = false;
  if (cmp == pos) {
    if (M != cmp && ct + abs(M - cmp) <= TM) ret |= dfs(M, ct + abs(M - cmp), M, clp);
    if (clp != cmp) ret |= dfs(clp, ct + abs(clp - cmp), clp, clp);
  }
  else ret |= dfs(cmp, ct + abs(cmp - pos), cmp, clp);

  if (clp == pos) {
    if (L != clp && ct + abs(L - clp) <= TL) ret |= dfs(L, ct + abs(L - clp), cmp, L);
    if (cmp != clp) ret |= dfs(cmp, ct + abs(cmp - clp), cmp, cmp);
  }
  else ret |= dfs(clp, ct + abs(clp - pos), cmp, clp);

  return d[{pos, ct, cmp, clp}] = ret;
}

void solve() {
  int m, l;
  cin >> m >> l >> M >> L >> TM >> TL;
  if (dfs(0, 0, m, l)) cout << "possible\n";
  else cout << "impossible\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
