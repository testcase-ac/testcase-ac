#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, v;
  cin >> n;
  map<int, int> ds;

  long long counter = 0;

  for (int i = 0; i < n; i++) {
    cin >> v;

    if (i == 0) ds[v] = 1;
    else {
      auto it = ds.upper_bound(v);
      int h = 0;

      if (it != ds.end()) h = it->second;
      if (it != ds.begin()) {
        --it;
        h = max(h, it->second);
      }

      counter += h;
      ds[v] = h + 1;
    }

    cout << counter << '\n';
  }
}
