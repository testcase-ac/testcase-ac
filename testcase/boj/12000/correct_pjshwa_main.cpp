#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int a[MAX];

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  int ms = 1e9;
  for (int i = 0; i < n; i++) {
    int s = 0;
    for (int j = 0; j < n; j++) {
      int d = (j + n - i) % n;
      s += a[j] * d;
    }
    ms = min(ms, s);
  }
  cout << ms << '\n';
}
