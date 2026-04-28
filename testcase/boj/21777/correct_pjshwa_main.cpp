#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int rem[MAX + 1];
int main() {
  fast_io();

  int n, x;
  cin >> n >> x;

  int lx, prio = 0;
  unordered_map<int, int> prio_map;
  vector<int> ais;

  prio_map[x] = prio;
  rem[x]++;
  ais.push_back(x);

  for (int i = 1; i < n; i++) {
    lx = x;
    cin >> x;
    if (x <= lx) prio--;
    rem[x]++;
    if (!prio_map.count(x)) {
      prio_map[x] = prio;
      ais.push_back(x);
    }
  }

  cout << ais.size() << '\n';
  sort(ais.begin(), ais.end());
  int prio_dt = -prio + 1;
  for (int ai : ais) cout << ai << ' ' << rem[ai] << ' ' << prio_map[ai] + prio_dt << '\n';
}
