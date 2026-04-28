#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1010;
int a[MAX];

int main() {
  fast_io();

  int n, t;
  cin >> n >> t;

  for (int i = 1; i <= n; i++) {
    int k;
    cin >> k;
    for (int j = 1; j <= k; j++) {
      int si, ei;
      cin >> si >> ei;
      for (int l = si; l < ei; l++) a[l]++;
    }
  }

  ll ans = 0;
  int st;
  for (int i = 0; i < MAX - t; i++) {
    ll cur = 0;
    for (int j = i; j < i + t; j++) cur += a[j];

    if (cur > ans) {
      ans = cur;
      st = i;
    }
  }

  cout << st << ' ' << st + t << '\n';
}
