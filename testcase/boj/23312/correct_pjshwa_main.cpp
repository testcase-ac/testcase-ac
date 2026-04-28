#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 193 * 193;
int ulim[MAX], icnt[MAX];

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int v, e;
    cin >> v >> e;
    icnt[i] = v - e;
    ulim[i] = i > 0 ? ulim[i - 1] + v : v;

    while (e--) {
      int ui, vi;
      cin >> ui >> vi;
    }
  }

  int q;
  cin >> q;
  while (q--) {
    int op, a, b;
    cin >> op;
    if (op == 1) {
      cin >> a;
      cout << icnt[a - 1] << '\n';
    }
    if (op == 2) {
      cin >> a >> b;
      icnt[lower_bound(ulim, ulim + n, a) - ulim]++;
    }
    if (op == 3) {
      cin >> a >> b;
      icnt[lower_bound(ulim, ulim + n, a) - ulim]--;
    }
  }
}
