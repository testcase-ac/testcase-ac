#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
pair<ll, ll> r[MAX];
bool vis[MAX];
int main() {
  fast_io();

  int n, j;

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> j;
    r[i] = {j, i};
  }
  sort(r, r + n);

  ll cnt, sum = 0;
  for (int i = 0; i < n; i++) {
    if (vis[i]) continue;

    j = i;
    cnt = 0;

    while (!vis[j]) {
      vis[j] = true;
      sum += r[j].first;
      cnt++;
      j = r[j].second;
    }

    sum += min(r[0].first * (cnt + 1) + r[i].first, r[i].first * (cnt - 2));
  }

  cout << sum;
}
