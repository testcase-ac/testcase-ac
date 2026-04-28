#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

pair<int, int> vs[1000];
int main() {
  fast_io();

  int n, s;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> s;
    vs[i] = make_pair(s, i);
  }
  sort(vs, vs + n);

  int cnt = 0;
  while (vs[n - 1].second != 0) {
    vs[n - 1].first--;
    for (int i = 0; i < n; i++) if (vs[i].second == 0) vs[i].first++;
    sort(vs, vs + n);
    cnt++;
  }

  cout << cnt;
}
