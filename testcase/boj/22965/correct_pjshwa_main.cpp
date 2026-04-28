#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int n;
int a[MAX], b[MAX];

bool already_sorted() {
  for (int i = 0; i < n; i++) if (a[i] != b[i]) return false;
  return true;
}

bool cyclic_shift() {
  int j = 0;
  while (a[j] != b[0]) j++;
  for (int i = 0; i < n; i++) if (a[(i + j) % n] != b[i]) return false;
  return true;
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i], b[i] = a[i];
  sort(b, b + n);

  if (already_sorted()) cout << 1;
  else if (cyclic_shift()) cout << 2;
  else cout << 3;
}
