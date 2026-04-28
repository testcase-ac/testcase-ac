#include <bits/stdc++.h>
typedef long long ll;
#define vl vector<ll>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

vl operator * (const vl &a, const vl &b) {
  int n = a.size();
  vl c(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (a[i] && b[j]) c[(i * j) % n] = 1;
    }
  }
  return c;
}

int main() {
  fast_io();

  ll k, m, n, s;
  cin >> k >> m >> n;

  vl a = vl(m);
  for (int i = 0; i < n; i++) {
    cin >> s;
    a[s] = 1;
  }

  // Identity
  vl ans = vl(m);
  ans[1] = 1;

  // Exponentiation by squaring
  while (k) {
    if (k & 1) ans = ans * a;
    a = a * a;
    k /= 2;
  }

  for (int i = 0; i < m; i++) {
    if (ans[i]) cout << i << ' ';
  }
  cout << '\n';
}
