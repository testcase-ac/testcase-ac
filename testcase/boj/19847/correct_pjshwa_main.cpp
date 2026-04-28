#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int n;
int a[(int)3e5];
int s[(int)1e6];

void oracle(int idx) {
  int nidx = idx + 1;
  while (nidx < n && a[idx] <= a[nidx]) nidx++;

  if (nidx == n) {
    for (int i = 0; i < a[idx]; i++) s[i] = i;
  }
  else {
    oracle(nidx);
    for (int i = a[nidx]; i < a[idx]; i++) s[i] = s[i % a[nidx]];
  }
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  oracle(0);
  double res = accumulate(s, s + a[0], 0LL);
  res /= a[0];
  cout << fixed << setprecision(12) << res << '\n';
}
