#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int parent[10001];

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) {
    memset(parent, 0, sizeof(parent));

    int n, x, y;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
      cin >> x >> y;
      parent[y] = x;
    }

    cin >> x >> y;
    vector<int> as;
    while (x) {
      as.push_back(x);
      x = parent[x];
    }
    sort(as.begin(), as.end());

    while (y) {
      if (*lower_bound(as.begin(), as.end(), y) == y) {
        cout << y << '\n';
        break;
      }
      y = parent[y];
    }
  }

}
