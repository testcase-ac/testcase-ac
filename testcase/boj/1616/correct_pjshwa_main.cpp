#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e7 + 1;
int e[MAX], k, m, n, out;

void dfs(int v) {
  int cv, nv;
  stack<int> s;
  s.push(v);
  while (!s.empty()) {
    cv = s.top();
    if (e[cv] >= 0) s.push((cv * k + e[cv]--) % n);
    else {
      if (out < n * k) {
        cout << cv % k << ' ';
        out++;
      }
      s.pop();
    }
  }
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  cin >> k >> m;
  if (m == 1) {
    for (int i = 0; i < k; i++) cout << i << ' ';
  }
  else {
    n = pow(k, m - 1);
    fill(e, e + n, k - 1);
    dfs(0);
  }
}
