#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int deg[100'001];
int main() {
  fast_io();

  int n, a, b, q, t, k;
  cin >> n;

  for (int i = 0; i < n - 1; i++) {
    cin >> a >> b;
    deg[a]++;
    deg[b]++;
  }

  cin >> q;
  while (q--) {
    cin >> t >> k;
    if (t == 1 && deg[k] == 1) cout << "no\n";
    else cout << "yes\n";
  }
}
