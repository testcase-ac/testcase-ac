#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;
  n *= 3;

  map<string, pair<int, int>> tally;
  string s;
  getline(cin, s);

  for (int i = 0; i < n; i++) {
    getline(cin, s);
    if (tally.count(s)) tally[s] = {tally[s].first + 1, i};
    else tally[s] = {1, i};
  }

  priority_queue<pair<pair<int, int>, string>> pq;
  for (auto t : tally) pq.push({t.second, t.first});

  while (k-- && !pq.empty()) {
    cout << pq.top().second << '\n';
    pq.pop();
  }
}
