#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int sndc[10000];
int fstc[10000];
int main() {
  fast_io();

  int n;
  cin >> n;

  long long s = 0;
  for (int i = 0; i < n; i++) {
    cin >> sndc[i];
    s += sndc[i];
  }
  s /= 3;

  long long v;
  if (n % 3 == 0) {
    fstc[0] = fstc[1] = 1;
    int mv;

    mv = 1e9;
    for (int i = 3; i < n; i += 3) {
      fstc[i] = sndc[i - 1] - sndc[i - 2] + fstc[i - 3];
      mv = min(fstc[i], mv);
    }
    fstc[0] += max(0, 1 - mv);

    mv = 1e9;
    for (int i = 4; i < n; i += 3) {
      fstc[i] = sndc[i - 1] - sndc[i - 2] + fstc[i - 3];
      mv = min(fstc[i], mv);
    }
    fstc[1] += max(0, 1 - mv);

    for (int i = 2; i < n; i++) fstc[i] = sndc[i - 1] - fstc[i - 1] - fstc[i - 2];
  }
  else if (n % 3 == 1) {
    v = 0;
    for (int i = 2; i < n; i += 3) v += sndc[i];
    fstc[0] = s - v;

    v = 0;
    for (int i = 3; i < n; i += 3) v += sndc[i];
    fstc[1] = s - v;

    for (int i = 2; i < n; i++) fstc[i] = sndc[i - 1] - fstc[i - 1] - fstc[i - 2];
  }
  else {
    v = 0;
    for (int i = 3; i < n; i += 3) v += sndc[i];
    long long a2sum1 = s - v;

    v = 0;
    for (int i = 4; i < n; i += 3) v += sndc[i];
    long long a2sum2 = s - v;

    fstc[2] = sndc[1] - a2sum1;
    fstc[3] = sndc[2] - a2sum2;
    fstc[1] = sndc[2] - fstc[2] - fstc[3];
    fstc[0] = sndc[1] - fstc[1] - fstc[2];
    for (int i = 2; i < n; i++) fstc[i] = sndc[i - 1] - fstc[i - 1] - fstc[i - 2];
  }

  for (int i = 0; i < n; i++) cout << fstc[i] << '\n';
}
