#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 40000, MOD = 123456789;
int lp[MAX + 1], d[MAX + 1];

int main() {
  fast_io();

  int n;
  cin >> n;

  vector<int> pr;
  for (int i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j=0; j<(int)pr.size() && pr[j]<=lp[i] && i*pr[j]<=MAX; ++j)
      lp[i * pr[j]] = pr[j];
  }

  d[0] = 1;
  for (int p : pr) {
    for (int i = 0; i <= MAX; i++) {
      if (i - p >= 0) {
        d[i] = (d[i] + d[i - p]) % MOD;
      }
    }
  }

  cout << d[n] << '\n';
}
