#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50000, INF = 1e9 + 7;
pii pos[MAX];

int main() {
  fast_io();

  int n;
  cin >> n;

  set<int> missing_breeds;
  for (int i = 0; i < n; i++) {
    cin >> pos[i].first >> pos[i].second;
    missing_breeds.insert(pos[i].second);
  }
  sort(pos, pos + n);

  int ans = INF;
  int ep = 0;
  unordered_map<int, int> tally;
  for (int sp = 0; sp < n; sp++) {
    while (ep < n && missing_breeds.size()) {
      tally[pos[ep].second]++;
      missing_breeds.erase(pos[ep].second);
      ep++;
    }

    if (!missing_breeds.size()) {
      ans = min(ans, pos[ep - 1].first - pos[sp].first);
    }

    tally[pos[sp].second]--;
    if (!tally[pos[sp].second]) missing_breeds.insert(pos[sp].second);
  }

  cout << ans << '\n';
}
