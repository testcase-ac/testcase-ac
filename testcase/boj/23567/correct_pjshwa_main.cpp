#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 10000, INF = 1e9 + 7;
int a[MAX];

unordered_map<int, int> in, ex;
int inc, exc;

void inc_update(int x, int diff) {
  if (diff < 0 && in[x] == 1) inc--;
  if (diff > 0 && in[x] == 0) inc++;
  in[x] += diff; 
}

void exc_update(int x, int diff) {
  if (diff < 0 && ex[x] == 1) exc--;
  if (diff > 0 && ex[x] == 0) exc++;
  ex[x] += diff; 
}

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> a[i], exc_update(a[i], 1);

  int ans = INF, ep = 0;
  for (int sp = 0; sp < n; sp++) {
    while (ep < n && inc < k) {
      inc_update(a[ep], +1);
      exc_update(a[ep], -1);
      ep++;
    }
    if (inc == k && exc == k) ans = min(ans, ep - sp);

    inc_update(a[sp], -1);
    exc_update(a[sp], +1);
  }

  cout << (ans == INF ? 0 : ans) << '\n';
}
