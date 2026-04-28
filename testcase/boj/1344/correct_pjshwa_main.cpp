#include <bits/stdc++.h>
using namespace std;

double probA[19], probB[19];

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  double a, b;
  cin >> a >> b;
  a /= 100;
  b /= 100;

  if (a == 1) {
    for (int i = 0; i <= 17; i++) probA[i] = 0;
    probA[18] = 1;
  }
  else {
    probA[0] = 1;
    for (int i = 1; i <= 18; i++) probA[0] *= (1 - a);
    for (int i = 1; i <= 18; i++) probA[i] = probA[i - 1] * (a * (19 - i)) / ((1 - a) * i);
  }

  if (b == 1) {
    for (int i = 0; i <= 17; i++) probB[i] = 0;
    probB[18] = 1;
  }
  else {
    probB[0] = 1;
    for (int i = 1; i <= 18; i++) probB[0] *= (1 - b);
    for (int i = 1; i <= 18; i++) probB[i] = probB[i - 1] * (b * (19 - i)) / ((1 - b) * i);
  }

  vector<int> npb = {0, 1, 4, 6, 8, 9, 10, 12, 14, 15, 16, 18};

  double p = 0;
  for (int nA : npb) {
    for (int nB : npb) p += probA[nA] * probB[nB];
  }

  cout << fixed << setprecision(12) << 1 - p;
}
