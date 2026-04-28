#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX];

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);

  for (int i = 0; i < n; i++) {
    if (a[n - i - 1] < i) return cout << i << '\n', 0;
  }
  cout << n << '\n';
}
