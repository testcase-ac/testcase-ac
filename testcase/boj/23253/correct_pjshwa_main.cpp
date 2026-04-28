#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5 + 1;
bool at_top[MAX];
int at[MAX];
stack<int> piles[MAX];

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;

  for (int i = 0; i < m; i++) {
    int k;
    cin >> k;
    for (int j = 0; j < k; j++) {
      int ki;
      cin >> ki;
      at[ki] = i;
      piles[i].push(ki);
    }
    at_top[piles[i].top()] = true;
  }

  for (int i = 1; i <= n; i++) {
    if (at_top[i]) {
      piles[at[i]].pop();
      if (!piles[at[i]].empty()) at_top[piles[at[i]].top()] = true;
    }
    else return cout << "No\n", 0;
  }

  cout << "Yes\n";
}
