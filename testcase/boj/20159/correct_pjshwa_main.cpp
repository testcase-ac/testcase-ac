#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int cards[100000];
int pff[50000];
int pfb[50000];
int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> cards[i];

  int j;
  pff[0] = cards[0];
  for (int i = 2; i < n; i += 2) {
    j = i / 2;
    pff[j] = pff[j - 1] + cards[i];
  }

  pfb[0] = cards[n - 1];
  for (int i = n - 3; i >= 0; i -= 2) {
    j = (n - 1 - i) / 2;
    pfb[j] = pfb[j - 1] + cards[i];
  }

  int maxv = max(pff[n / 2 - 1], pfb[n / 2 - 1]);
  for (int i = 0; i < n / 2 - 1; i++) {
    maxv = max(maxv, pff[i] + pfb[n / 2 - 2 - i]);
    maxv = max(maxv, pff[i] + pfb[n / 2 - 1 - i] - pfb[0]);
  }
  cout << maxv << '\n';
}
