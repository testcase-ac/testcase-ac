#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 80000;
int pv[MAX + 1], last[MAX + 1];

int main() {
  fast_io();

  int q;
  cin >> q;
  pv[0] = last[0] = -1;

  // dfs sort of
  for (int i = 1; i <= q; i++) {
    string op;
    int c;
    cin >> op;
    if (op == "a") {
      cin >> c;
      pv[i] = i - 1;
      last[i] = c;
    }
    if (op == "s") {
      pv[i] = pv[pv[i - 1]];
      last[i] = last[pv[i - 1]];
    }
    if (op == "t") {
      cin >> c;
      pv[i] = pv[c - 1];
      last[i] = last[c - 1];
    }

    cout << last[i] << '\n';
  }
}
