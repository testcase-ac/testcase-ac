#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2000;
int a[MAX];

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  int sum = 0, day = 0;
  for (int i = 1; i < n; i++) {
    if (a[i] > a[0]) {
      sum += a[i] - a[0];
      day++;
    }
  }

  cout << sum << ' ' << day << '\n';
}
