#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

pii pillars[1000];
int main() {
  fast_io();

  int n, l, h, maxh = -1;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> l >> h;
    maxh = max(h, maxh);
    pillars[i] = {l, h};
  }
  sort(pillars, pillars + n);

  int curl = 0, curh = 0, area = 0;
  int i = 0;
  while (1) {
    area += (pillars[i].first - curl) * curh;
    curl = pillars[i].first;
    curh = max(curh, pillars[i].second);
    i++;

    if (curh == maxh) break;
  }

  int curr = 1001;
  curh = 0;
  i = n - 1;
  while (1) {
    area += (curr - pillars[i].first - 1) * curh;
    curr = pillars[i].first + 1;
    curh = max(curh, pillars[i].second);
    i--;

    if (curh == maxh) break;
  }

  area += (curr - curl) * maxh;
  cout << area << '\n';
}
