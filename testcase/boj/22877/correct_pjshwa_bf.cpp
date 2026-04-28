#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n;
string a, la;
void exchange(int i) {
  if (
    a[i] == 'S' && a[i + 1] == 'P' ||
    a[i] == 'P' && a[i + 1] == 'R' ||
    a[i] == 'R' && a[i + 1] == 'S'
  ) swap(a[i], a[i + 1]);
}

void round() {
  for (int i = 0; i < n - 1; i++) exchange(i);
}

int main() {
  fast_io();

  int t;
  cin >> n >> t >> a;

  for (int i = 0; i < t; i++) {
    la = a;
    round();
    if (la == a) return cout << a, 0;
  }
  cout << a;
}
