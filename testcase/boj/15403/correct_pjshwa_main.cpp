#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
set<int> q[MAX + 1];
int a[MAX + 1];

int main() {
  fast_io();

  int n, x;
  cin >> n;

  for (int i = 1; i <= n; i++) {
    cin >> x;
    q[x].insert(i);
  }

  int dn = n;
  for (int i = 1; i <= n; i++) {
    for (int e : q[i]) {
      a[e] = dn;
      dn--;
    }
  }

  for (int i = 1; i <= n; i++) {
    cout << a[i] << " ";
  }
}
