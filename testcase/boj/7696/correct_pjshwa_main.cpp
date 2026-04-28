#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int LIM = 1e6;
vector<int> D;
int C[10], x;

void nPr(int n, int r, int f) {
  if (D.size() > LIM) return;

  if (r == 0) return D.push_back(x);

  for (int i = f; i < 10; i++) {
    if (C[i]) continue;
    C[i] = 1;
    x = x * 10 + i;
    nPr(n, r - 1, 0);
    x /= 10;
    C[i] = 0;
  }
}


int main() {
  fast_io();

  for (int i = 1; i <= 8; i++) nPr(10, i, 1);

  int n;
  while (cin >> n) {
    if (n == 0) break;
    cout << D[n - 1] << '\n';
  }
}
