#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int degree[13];
vector<int> g[13];
int main() {
  fast_io();

  int j, k;
  for (int i = 1; i <= 12; i++) {
    cin >> j >> k;
    degree[j]++;
    degree[k]++;

    g[j].push_back(k);
    g[k].push_back(j);
  }

  for (int i = 1; i <= 12; i++) {
    if (degree[i] != 3) continue;

    vector<int> dgs;
    for (int a : g[i]) dgs.push_back(degree[a]);
    sort(dgs.begin(), dgs.end());

    if (dgs[0] == 1 && dgs[1] == 2 && dgs[2] == 3) cout << i;
  }
}
