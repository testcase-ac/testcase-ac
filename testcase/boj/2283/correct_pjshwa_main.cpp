#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int MAX = 1e6;
int delta[MAX + 5];

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    int s, e;
    cin >> s >> e;
    delta[s]++;
    delta[e]--;
  }

  int lp = 0, rp = 0;
  int ldelta = 0, rdelta = 0;
  ll csum = 0;

  while (rp <= MAX) {
    if (csum <= k) {
      if (csum == k) return cout << lp << ' ' << rp, 0;
      rdelta += delta[rp];
      csum += rdelta;
      rp++;
    }
    else {
      ldelta += delta[lp];
      csum -= ldelta;
      lp++;
    }
  }

  cout << "0 0";
}
