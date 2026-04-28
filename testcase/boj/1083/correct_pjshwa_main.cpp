#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int a[50], n, s;

void bring(int spos) {
  int bpos = spos, mv = a[spos];
  for (int i = spos + 1; i <= min(n - 1, spos + s); i++) {
    if (a[i] > mv) {
      bpos = i;
      mv = a[i];
    }
  }
  if (spos != bpos) {
    int nv = a[bpos];
    for (int i = bpos - 1; i >= spos; i--) a[i + 1] = a[i];
    a[spos] = nv;
  }
  s -= (bpos - spos);
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  cin >> s;
  for (int i = 0; i < n - 1; i++) bring(i);
  for (int i = 0; i < n; i++) cout << a[i] << ' ';
}
