#include <bits/stdc++.h>
#define ll long long
using namespace std;


void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1e9 + 7, MAX = 1e6 + 1;
ll d[MAX], ew[MAX];

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    a[i] = abs(a[i]);
  }

  set<int> s;
  for (int i = 0; i < n; i++) {
    s.insert(a[i]);
  }

  for (int i = 0; i < m - 1; i++) {
    set<int> ns;
    for (int e : s) for (int j = 0; j < n; j++) ns.insert(e ^ a[j]);
    s = ns;
  }

  int mx = -1;
  for (int e : s) {
    mx = max(mx, e);
  }

  cout << mx << '\n';
}
