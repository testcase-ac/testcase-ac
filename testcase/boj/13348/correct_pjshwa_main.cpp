#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;

  int tscore = 0, ascore = 0;
  unordered_map<string, set<int>> p;
  set<int> revealed;

  for (int i = 0; i < k; i++) {
    int c1, c2;
    string p1, p2;
    cin >> c1 >> c2 >> p1 >> p2;

    p[p1].insert(c1);
    p[p2].insert(c2);
    revealed.insert(c1);
    revealed.insert(c2);
    if (p1 == p2) ascore++;
  }

  int unmatched = 0;
  for (auto [_, s] : p) {
    if (s.size() == 2) tscore++;
    else unmatched++;
  }
  int unrevealed = n - revealed.size();
  
  tscore -= ascore;
  if (unmatched == unrevealed) tscore += unmatched;
  else if (unrevealed == 2) tscore++;
  cout << tscore << '\n';
}
