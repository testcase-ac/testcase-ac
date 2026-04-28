#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;
  list<pair<int, int>> ls;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= k; j++) {
      int c;
      cin >> c;
      ls.push_back({i, c});
    }
  }

  int rep = n * k - 1;
  auto lsi = ls.begin();
  while (rep--) {
    int t = (*lsi).second - 1;
    lsi = ls.erase(lsi);
    if (lsi == ls.end()) lsi = ls.begin();

    while (t--) {
      lsi++;
      if (lsi == ls.end()) lsi = ls.begin();
    }

  }

  auto p = *lsi;
  cout << p.first << " " << p.second;
}
