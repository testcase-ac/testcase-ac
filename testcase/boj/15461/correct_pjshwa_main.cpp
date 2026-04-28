#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define compress(x) sort(all(x)), (x).erase(unique(all(x)), (x).end())
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, g;
  cin >> n >> g;
  map<int, int> prods;
  map<int, int> cprod;
  prods[0] = 1;
  cprod[0] = 0;

  vector<tuple<int, int, int>> updates;
  vector<int> days;
  for (int i = 0; i < n; i++) {
    int x, y, z;
    cin >> x >> y >> z;
    days.push_back(x);
    prods[0]++;
    cprod[y] = 0;
    updates.push_back(make_tuple(x, y, z));
  }
  sort(updates.begin(), updates.end());
  compress(days);

  int uc = 0, usz = updates.size();
  int winning = 0, changes = 0;
  bool changed;
  for (int day : days) {
    changed = false;
    int us = uc, ue = uc;
    while (ue < usz && get<0>(updates[ue]) <= day) ue++;

    int oc = prods[winning];

    for (int ui = us; ui < ue; ui++) {
      int y = get<1>(updates[ui]), z = get<2>(updates[ui]);
      prods[cprod[y]]--;
      if (prods[cprod[y]] == 0) prods.erase(cprod[y]);

      cprod[y] += z;
      prods[cprod[y]]++;
    }

    int next_winning = prods.rbegin()->first;
    for (int ui = us; ui < ue; ui++) {
      int y = get<1>(updates[ui]), z = get<2>(updates[ui]);
      if ((cprod[y] - z == winning) ^ (cprod[y] == next_winning)) changed = true;
    }

    changed |= oc != prods[next_winning];
    if (changed) changes++;
    uc = ue;
    winning = next_winning;
  }

  cout << changes << '\n';
}
