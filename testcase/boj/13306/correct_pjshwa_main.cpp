#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int parent[MAX + 1], pnode[MAX + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x != y) parent[y] = x;
}

int main() {
  fast_io();

  int n, q;
  cin >> n >> q;
  for (int i = 1; i <= n; i++) parent[i] = i;
  for (int i = 2; i <= n; i++) cin >> pnode[i];

  q += (n - 1);
  stack<pair<int, int>> qs;
  while (q--) {
    int t, ai, bi;
    cin >> t >> ai;
    if (t == 0) qs.push({ai, -1});
    else {
      cin >> bi;
      qs.push({ai, bi});
    }
  }

  stack<bool> as;
  while (!qs.empty()) {
    auto[ai, bi] = qs.top();
    qs.pop();

    if (bi == -1) Union(pnode[ai], ai);
    else as.push(Find(ai) == Find(bi));
  }

  while (!as.empty()) {
    cout << (as.top() ? "YES" : "NO") << '\n';
    as.pop();
  }

}
