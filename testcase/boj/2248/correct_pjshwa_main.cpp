#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll d[32][32];
ll f(int n, int k) {
  if (n == 1) return k == 0 ? 1 : 2;
  if (k == 0) return 1;
  if (d[n][k] != -1) return d[n][k];

  return d[n][k] = f(n - 1, k) + f(n - 1, k - 1);
}

string g(int n, int k, unsigned int c) {
  if (n == 1) return c == 1 ? "0" : "1";
  if (c <= f(n - 1, k)) return "0" + g(n - 1, k, c);
  else return "1" + g(n - 1, k - 1, c - f(n - 1, k));
}

int main() {
  fast_io();

  memset(d, -1, sizeof(d));
  int n, k;
  unsigned int c;
  cin >> n >> k >> c;
  cout << g(n, k, c);
}
