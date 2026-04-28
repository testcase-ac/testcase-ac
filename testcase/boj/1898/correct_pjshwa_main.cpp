#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50000;
int a[MAX + 1], inv[MAX + 1];

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    inv[a[i]] = i;
  }

  int cur = n;
  while (cur > 1) {
    if (inv[cur] < inv[cur - 1]) {
      swap(a[inv[cur]], a[inv[cur - 1]]);
      cur -= 2;
    }
    else cur--;
  }

  for (int i = 1; i <= n; i++) cout << a[i] << '\n';
}
