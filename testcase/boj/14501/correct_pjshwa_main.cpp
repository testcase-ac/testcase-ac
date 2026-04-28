#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1.5e6;
int a[MAX], dur[MAX], d[MAX + 50];

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int ti, pi;
    cin >> ti >> pi;
    a[i] = pi;
    dur[i] = ti;
  }

  for (int i = 0; i <= n; i++) {
    if (i > 0) d[i] = max(d[i], d[i - 1]);
    if (i < n) d[i + dur[i]] = max(d[i + dur[i]], d[i] + a[i]);
  }
  cout << d[n];
}
