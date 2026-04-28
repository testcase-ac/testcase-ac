#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n;
  cin >> n;
  ll a = 0, lv = n + 1;
  int lim = sqrt(n);

  for (int i = 1; i <= lim; i++) {
    int s = (n - 1) / i + 1;
    a += (lv - s) * i;
    lv = s;
  }

  for (int i = 1; i < lv; i++) {
    int s = (n - 1) / i + 1;
    a += s;
  }

  cout << a;
}
